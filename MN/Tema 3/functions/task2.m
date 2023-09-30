## Copyright (C) 2023 Andrei
##
## This program is free software: you can redistribute it and/or modify
## it under the terms of the GNU General Public License as published by
## the Free Software Foundation, either version 3 of the License, or
## (at your option) any later version.
##
## This program is distributed in the hope that it will be useful,
## but WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
## GNU General Public License for more details.
##
## You should have received a copy of the GNU General Public License
## along with this program.  If not, see <https://www.gnu.org/licenses/>.

## -*- texinfo -*-
## @deftypefn {} {@var{retval} =} task2 (@var{input1}, @var{input2})
##
## @seealso{}
## @end deftypefn

## Author: Andrei <Andrei@DESKTOP-PK505U9>
## Created: 2023-02-28

function new_X = task2 (photo, pcs)
  [m n] = size(photo);

  % initializare matrice finala.
  new_X = zeros(m, n);

  % TODO: cast photo la double.
  photo = double(photo);

  % TODO: normalizeaza matricea initiala scazand din ea media fiecarui rand.
  rowsMiu = mean(photo, 2);
  reworkedPhoto = photo - rowsMiu;

  % TODO: construieste matricea Z.
  Z = reworkedPhoto' / sqrt(n - 1);

  % TODO: calculeaza matricile U, S si V din SVD aplicat matricii Z
  [U, S, V] = svd(Z);

  % TODO: construieste matricea W din primele pcs coloane ale lui V
  W = V(:, 1 : pcs);

  % TODO: cacluleaza matricea Y
  Y = W' * reworkedPhoto;

  % TODO: aproximeaza matricea initiala
  new_X = W * Y + rowsMiu;

  % TODO: transforma matricea in uint8 pentru a fi o imagine valida.
  new_X = uint8(new_X);
endfunction
