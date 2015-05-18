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


/*
 * STOKE Test Suite
 * Initial Version: September 22nd, 2014
 * Author: Berkeley Churchill <berkeleychurchill@gmail.com>
 *
 * Google test comes with macros to register tests.  Whenever
 * you create a new test, all you need is to use the TEST macro,
 * as you can see in any of the .cc files in this folder.  The
 * only thing the test framework needs is to #include all of
 * these functions into one big compilation unit.  Thus, this
 * file has a list of all the .cc files with tests in them.
 * Update this file, and you won't need to touch any makefiles :)
 *
 */


#include "tests/analysis/analysis.h"
#include "tests/cfg/cfg.h"
#include "tests/cost/cost.h"
#include "tests/cpputil/cpputil.h"
#include "tests/disassembler/disassembler.h"
#include "tests/fixture.h"
#include "tests/integration/integration.h"
#include "tests/sandbox/sandbox.h"
#include "tests/search/search.h"
#include "tests/solver/solver.h"
#include "tests/state/state.h"
#include "tests/stategen/stategen.h"
#include "tests/symstate/bitvector.h"
#include "tests/trivial.h"
#include "tests/tunit/tunit.h"
#include "tests/validator/validator.h"
#include "tests/x64asm/x64asm.h"


INSTANTIATE_TEST_CASE_P(
  AllFixtures,
  CodeFixtureTest,
  ::testing::ValuesIn(CodeFixtureTestInit::get_fixtures())
);

