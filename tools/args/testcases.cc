// Copyright 2013-2015 Stanford University
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "tools/args/testcases.h"

#include <limits>

using namespace cpputil;
using namespace std;

namespace stoke {

namespace {
set<size_t> create_default_testcase_set() {
  vector<size_t> n(10000);
  iota(n.begin(), n.end(), 0);
  return set<size_t>(n.begin(), n.end());
}
}

Heading& testcases_heading =
  Heading::create("Testcase Options:");

FileArg<CpuStates, CpuStatesReader, CpuStatesWriter>& testcases_arg =
  FileArg<CpuStates, CpuStatesReader, CpuStatesWriter>::create("testcases")
  .usage("<path/to/file>")
  .description("Testcases");

FlagArg& shuffle_tc_arg =
  FlagArg::create("shuffle_testcases")
  .description("Shuffle testcase ordering");

const set<size_t> default_set = create_default_testcase_set();

ValueArg<set<size_t>, SpanReader<set<size_t>, Range<size_t, 0, 1024 * 1024>>>& training_set_arg =
  ValueArg<set<size_t>, SpanReader<set<size_t>, Range<size_t, 0, 1024 * 1024>>>::create("training_set")
  .usage("{ 0 1 ... 9 }")
  .description("Subset of testcase indices to use for training sets")
  .default_val(default_set);

ValueArg<set<size_t>, SpanReader<set<size_t>, Range<size_t, 0, 1024 * 1024>>>& test_set_arg =
  ValueArg<set<size_t>, SpanReader<set<size_t>, Range<size_t, 0, 1024 * 1024>>>::create("test_set")
  .usage("{ 0 1 ... 9 }")
  .description("Subset of testcase indices to use for test sets")
  .default_val(default_set);

ValueArg<size_t>& testcase_idx_arg =
  ValueArg<size_t>::create("index")
  .usage("<int>")
  .description("Testcase index")
  .default_val(0);

} // namespace stoke
