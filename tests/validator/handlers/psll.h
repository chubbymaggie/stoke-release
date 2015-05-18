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


class ValidatorPsllTest : public ValidatorTest { };


TEST_F(ValidatorPsllTest, DISABLED_Identity) {

  target_ << "pslld %xmm0, %xmm0" << std::endl;
  target_ << "retq" << std::endl;

  rewrite_ << "pslld %xmm0, %xmm0" << std::endl;
  rewrite_ << "retq" << std::endl;

  assert_equiv();
}



TEST_F(ValidatorPsllTest, DISABLED_NotANop) {

  target_ << "pslld %xmm0, %xmm0" << std::endl;
  target_ << "retq" << std::endl;

  rewrite_ << "retq" << std::endl;

  assert_ceg();
}


