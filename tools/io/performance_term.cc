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

#include <array>
#include <string>
#include <utility>

#include "tools/io/generic.h"
#include "tools/io/performance_term.h"

using namespace std;
using namespace stoke;

namespace {

array<pair<string, PerformanceTerm>, 4> pts {{
    {"none", PerformanceTerm::NONE},
    {"size", PerformanceTerm::SIZE},
    {"latency", PerformanceTerm::LATENCY},

    // Add user-defined extensions here ...
    {"extension", PerformanceTerm::EXTENSION}
  }
};

} // namespace

namespace stoke {

void PerformanceTermReader::operator()(std::istream& is, PerformanceTerm& pt) {
  string s;
  is >> s;
  if (!generic_read(pts, s, pt)) {
    is.setstate(ios::failbit);
  }
}

void PerformanceTermWriter::operator()(std::ostream& os, const PerformanceTerm pt) {
  string s;
  generic_write(pts, s, pt);
  os << s;
}

} // namespace stoke
