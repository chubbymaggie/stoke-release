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

#include <cstdlib>
#include <stdint.h>

extern void saxpy(uint32_t a, uint32_t* x, uint32_t* y, int i);

int main(int argc, char** argv) {
  const auto itr = argc > 1 ? atoi(argv[1]) : 1024;
  const auto seed = argc > 2 ? atoi(argv[2]) : 0;

  srand(seed);

  for (auto i = 0; i < itr; ++i) {
    auto a = rand();
    auto x = new uint32_t[16];
    auto y = new uint32_t[16];

    auto idx = 4 * (rand() % 4);
    for (auto j = 0; j < 4; ++j) {
      x[idx+j] = rand();
      y[idx+j] = rand();
    }

    saxpy(a, x, y, idx);
  }

  return 0;
}
