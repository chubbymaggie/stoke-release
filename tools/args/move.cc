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

#include "tools/args/move.h"

using namespace cpputil;

namespace stoke {

Heading& move_heading =
  Heading::create("Transformation Type Options:");

ValueArg<Move, MoveReader, MoveWriter>& move_arg =
  ValueArg<Move, MoveReader, MoveWriter>::create("move_type")
  .usage("(instruction|opcode|operand|local_swap|global_swap|resize|extension)")
  .description("Move type to perform")
  .default_val(Move::INSTRUCTION);

} // namespace stoke
