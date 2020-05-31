// Arline Quantum
// Copyright (C) 2019-2020 Turation Ltd
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Affero General Public License as
// published by the Free Software Foundation, either version 3 of the
// License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.
//
//
// Being originated from Qiskit package, this file has been modified by Turation Ltd
//
//
// Original code is licensed as stated below:
//
// This code is part of Qiskit.
//
// (C) Copyright IBM 2017.
//
// This code is licensed under the Apache License, Version 2.0. You may
// obtain a copy of this license in the LICENSE.txt file in the root directory
// of this source tree or at http://www.apache.org/licenses/LICENSE-2.0.
//
// Any modifications or derivative works of this code must retain this
// copyright notice, and modified files need to carry a notice indicating
// that they have been altered from the originals.
//
//
// Arline Quantum Standard Header


// --- QE Hardware primitives ---

// 3-parameter 2-pulse single qubit gate
gate u3(theta,phi,lambda) q { U(theta,phi,lambda) q; }
// 2-parameter 1-pulse single qubit gate
gate u2(phi,lambda) q { U(pi/2,phi,lambda) q; }
// 1-parameter 0-pulse single qubit gate
gate u1(lambda) q { U(0,0,lambda) q; }
// controlled-NOT
gate cx c,t { CX c,t; }
// idle gate (identity)
gate id a { U(0,0,0) a; }
// idle gate (identity) with length gamma*sqglen
gate u0(gamma) q { U(0,0,0) q; }

// --- QE Standard Gates ---

// Pauli gate: bit-flip
gate x a { u3(pi,0,pi) a; }
// Pauli gate: bit and phase flip
gate y a { u3(pi,pi/2,pi/2) a; }
// Pauli gate: phase flip
gate z a { u1(pi) a; }
// Clifford gate: Hadamard
gate h a { u2(0,pi) a; }
// Clifford gate: sqrt(Z) phase gate
gate s a { u1(pi/2) a; }
// Clifford gate: conjugate of sqrt(Z)
gate sdg a { u1(-pi/2) a; }
// C3 gate: sqrt(S) phase gate
gate t a { u1(pi/4) a; }
// C3 gate: conjugate of sqrt(S)
gate tdg a { u1(-pi/4) a; }

// --- Standard rotations ---
// Rotation around X-axis
gate rx(theta) a { u3(theta, -pi/2,pi/2) a; }
// rotation around Y-axis
gate ry(theta) a { u3(theta,0,0) a; }
// rotation around Z axis
gate rz(phi) a { u1(phi) a; }

// --- QE Standard User-Defined Gates  ---

// controlled-Phase
gate cz a,b { h b; cx a,b; h b; }
// controlled-Y
gate cy a,b { sdg b; cx a,b; s b; }
// swap
gate swap a,b { cx a,b; cx b,a; cx a,b; }
// controlled-H
gate ch a,b {
h b; sdg b;
cx a,b;
h b; t b;
cx a,b;
t b; h b; s b; x b; s a;
}
// generalized rotation
gate r(theta, phi) a { u3(theta, phi - pi / 2, -phi + pi / 2) a; }
// C3 gate: Toffoli
gate ccx a,b,c
{
  h c;
  cx b,c; tdg c;
  cx a,c; t c;
  cx b,c; tdg c;
  cx a,c; t b; t c; h c;
  cx a,b; t a; tdg b;
  cx a,b;
}
// cswap (Fredkin)
gate cswap a,b,c
{
  cx c,b;
  ccx a,b,c;
  cx c,b;
}
// controlled rx rotation
gate crx(lambda) a,b
{
  u1(pi/2) b;
  cx a,b;
  u3(-lambda/2,0,0) b;
  cx a,b;
  u3(lambda/2,-pi/2,0) b;
}
// controlled ry rotation
gate cry(lambda) a,b
{
  u3(lambda/2,0,0) b;
  cx a,b;
  u3(-lambda/2,0,0) b;
  cx a,b;
}
// controlled rz rotation
gate crz(lambda) a,b
{
  u1(lambda/2) b;
  cx a,b;
  u1(-lambda/2) b;
  cx a,b;
}
// controlled phase rotation
gate cu1(lambda) a,b
{
  u1(lambda/2) a;
  cx a,b;
  u1(-lambda/2) b;
  cx a,b;
  u1(lambda/2) b;
}
// controlled-U
gate cu3(theta,phi,lambda) c, t
{
  // implements controlled-U(theta,phi,lambda) with  target t and control c
  u1((lambda+phi)/2) c;
  u1((lambda-phi)/2) t;
  cx c,t;
  u3(-theta/2,0,-(phi+lambda)/2) t;
  cx c,t;
  u3(theta/2,phi,0) t;
}
// two-qubit XX rotation
gate rxx(theta) a,b
{
  u3(pi/2, theta, 0) a;
  h b;
  cx a,b;
  u1(-theta) b;
  cx a,b;
  h b;
  u2(-pi, pi-theta) a;
}
// two-qubit YY rotation
gate ryy(theta) a,b
{
  u3(pi/2, -pi/2,pi/2) a;
  u3(pi/2, -pi/2,pi/2) b;
  cx a,b;
  u1(theta) b;
  cx a,b;
  u3(-pi/2, -pi/2,pi/2) a;
  u3(-pi/2, -pi/2,pi/2) b;
}
// two-qubit ZZ rotation
gate rzz(theta) a,b
{
  cx a,b;
  u1(theta) b;
  cx a,b;
}
// relative-phase CCX
gate rccx a,b,c
{
  u2(0,pi) c;
  u1(pi/4) c;
  cx b, c;
  u1(-pi/4) c;
  cx a, c;
  u1(pi/4) c;
  cx b, c;
  u1(-pi/4) c;
  u2(0,pi) c;
}
// relative-phase 3-controlled X gate
gate rc3x a,b,c,d
{
  u2(0,pi) d;
  u1(pi/4) d;
  cx c,d;
  u1(-pi/4) d;
  u2(0,pi) d;
  cx a,d;
  u1(pi/4) d;
  cx b,d;
  u1(-pi/4) d;
  cx a,d;
  u1(pi/4) d;
  cx b,d;
  u1(-pi/4) d;
  u2(0,pi) d;
  u1(pi/4) d;
  cx c,d;
  u1(-pi/4) d;
  u2(0,pi) d;
}
// 3-controlled X gate
gate c3x a,b,c,d
{
    h d; cu1(-pi/4) a,d; h d;
    cx a,b;
    h d; cu1(pi/4) b,d; h d;
    cx a,b;
    h d; cu1(-pi/4) b,d; h d;
    cx b,c;
    h d; cu1(pi/4) c,d; h d;
    cx a,c;
    h d; cu1(-pi/4) c,d; h d;
    cx b,c;
    h d; cu1(pi/4) c,d; h d;
    cx a,c;
    h d; cu1(-pi/4) c,d; h d;
}
// 3-controlled sqrt(X) gate, this equals the C3X gate where the CU1 rotations are -pi/8 not -pi/4
gate c3sqrtx a,b,c,d
{
    h d; cu1(-pi/8) a,d; h d;
    cx a,b;
    h d; cu1(pi/8) b,d; h d;
    cx a,b;
    h d; cu1(-pi/8) b,d; h d;
    cx b,c;
    h d; cu1(pi/8) c,d; h d;
    cx a,c;
    h d; cu1(-pi/8) c,d; h d;
    cx b,c;
    h d; cu1(pi/8) c,d; h d;
    cx a,c;
    h d; cu1(-pi/8) c,d; h d;
}
// 4-controlled X gate
gate c4x a,b,c,d,e
{
    h e; cu1(-pi/2) d,e; h e;
    c3x a,b,c,d;
    h d; cu1(pi/4) d,e; h d;
    c3x a,b,c,d;
    c3sqrtx a,b,c,e;
}