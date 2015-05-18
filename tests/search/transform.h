// Copyright 2013-2015 Stanford University
//
// Licensed under the Apache License, Version 2.0 (the License);
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an AS IS BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.


#include <sys/time.h>
#include "src/cfg/cfg.h"
#include "src/cost/cost.h"
#include "src/cost/cost_function.h"
#include "src/cost/performance_term.h"
#include "src/search/transforms.h"
#include "src/stategen/stategen.h"

class TransformsTest : public CodeFixtureTest {

public:

  virtual void SetUp() {
    CodeFixtureTest::SetUp();

    iterations_ = 10000;

    struct timeval tv;
    gettimeofday(&tv, NULL);

    seed_ = (std::default_random_engine::result_type)(tv.tv_sec * 1000000 + tv.tv_usec);
    transforms_.set_seed(seed_);

    // Note: we only want to do this once.
    if (!transforms_init_) {
      transforms_.set_opcode_pool(x64asm::FlagSet::universe(), 0, 0, true, true, {}, {});
      transforms_init_ = true;
    }

    /* set operands based on the target */
    transforms_.set_operand_pool(GetParam().get_code(), x64asm::RegSet::empty());

    code_ = GetParam().get_code();
    cfg_ = new stoke::Cfg(code_, x64asm::RegSet::universe(), x64asm::RegSet::empty());
  }

protected:

  static stoke::Transforms transforms_;

  size_t iterations_;
  std::default_random_engine::result_type seed_;
  x64asm::Code code_;
  stoke::Cfg* cfg_;

private:
  static bool transforms_init_;
};

bool TransformsTest::transforms_init_ = false;
stoke::Transforms TransformsTest::transforms_;

TEST_P(TransformsTest, InstructionMoveIsReversible) {

  int success = 0;
  x64asm::Code original(code_);

  for (size_t i = 0; i < iterations_; ++i) {

    if (transforms_.instruction_move(*cfg_)) {
      success++;
      transforms_.undo_instruction_move(*cfg_);
    }

    ASSERT_EQ(original, cfg_->get_code()) <<
                                          "and the seed was: " << seed_ << std::endl;

  }
}

TEST_P(TransformsTest, OpcodeMoveIsReversible) {

  int success = 0;
  x64asm::Code original(code_);

  for (size_t i = 0; i < iterations_; ++i) {

    if (transforms_.opcode_move(*cfg_)) {
      success++;
      transforms_.undo_opcode_move(*cfg_);
    }

    ASSERT_EQ(original, cfg_->get_code()) <<
                                          "and the seed was: " << seed_ << std::endl;

  }
}

TEST_P(TransformsTest, OperandMoveIsReversible) {

  int success = 0;
  x64asm::Code original(code_);

  for (size_t i = 0; i < iterations_; ++i) {

    if (transforms_.operand_move(*cfg_)) {
      success++;
      transforms_.undo_operand_move(*cfg_);
    }

    ASSERT_EQ(original, cfg_->get_code()) <<
                                          "and the seed was: " << seed_ << std::endl;

  }
}

TEST_P(TransformsTest, ResizeMoveIsReversible) {

  int success = 0;
  x64asm::Code original(code_);

  for (size_t i = 0; i < iterations_; ++i) {

    if (transforms_.resize_move(*cfg_)) {
      success++;
      transforms_.undo_resize_move(*cfg_);
    }

    ASSERT_EQ(original, cfg_->get_code()) <<
                                          "and the seed was: " << seed_ << std::endl;

  }
}

TEST_P(TransformsTest, LocalSwapIsReversible) {

  int success = 0;
  x64asm::Code original(code_);

  for (size_t i = 0; i < iterations_; ++i) {

    if (transforms_.local_swap_move(*cfg_)) {
      success++;
      transforms_.undo_local_swap_move(*cfg_);
    }

    ASSERT_EQ(original, cfg_->get_code()) <<
                                          "and the seed was: " << seed_ << std::endl;

  }
}

TEST_P(TransformsTest, GlobalSwapIsReversible) {

  int success = 0;
  x64asm::Code original(code_);

  for (size_t i = 0; i < iterations_; ++i) {

    if (transforms_.global_swap_move(*cfg_)) {
      success++;
      transforms_.undo_global_swap_move(*cfg_);
    }

    ASSERT_EQ(original, cfg_->get_code()) <<
                                          "and the seed was: " << seed_ << std::endl;

  }
}

TEST_P(TransformsTest, CostInvariantAfterUndo) {

  code_.push_back(x64asm::Instruction(x64asm::RET));
  x64asm::Code original(code_);
  cfg_ = new stoke::Cfg(code_, x64asm::RegSet::universe(), x64asm::RegSet::empty());

  stoke::Sandbox sb;
  sb.set_max_jumps(30).set_abi_check(false);

  //attempt to make a testcase
  // there's an underlying bug here in stoke testcase.
  /*
  std::cout << "generating testcase" << std::endl;
  std::cout << "cfg: " << cfg_->get_code() << std::endl;
  */
  stoke::CpuState tc;
  /*
  stoke::StateGen sg(&sb);
  if (sg.get(tc, *cfg_))
  */
  sb.insert_input(tc);

  //make cost function
  stoke::CostFunction fxn(&sb);
  fxn.set_target(*cfg_, true, true)
  .set_performance_term(stoke::PerformanceTerm::LATENCY);

  auto original_cost = fxn({original, x64asm::RegSet::universe(), x64asm::RegSet::empty()});

  //loop and check
  for (size_t i = 0; i < iterations_; ++i) {

    stoke::Move m = (stoke::Move)(i % 6);
    if (transforms_.modify(*cfg_, m)) {
      transforms_.undo(*cfg_, m);
    }

    ASSERT_EQ(original_cost, fxn(*cfg_)) <<
                                         "the original code: " << std::endl << original << std::endl <<
                                         "the modified code: " << std::endl << cfg_->get_code() << std::endl <<
                                         "and the seed was: " << seed_ << std::endl;

    ASSERT_EQ(fxn(*cfg_), fxn(*cfg_)) << "evaluating cost twice failed.";
  }


}


INSTANTIATE_TEST_CASE_P(
  AllFixtures,
  TransformsTest,
  ::testing::ValuesIn(CodeFixtureTestInit::get_fixtures())
);
