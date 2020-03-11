/*
Copyright 2019 biopuppet

LogJudge is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License (LGPL) as
published by the Free Software Foundation, either version 3 of the
License, or (at your option) any later version.

LogJudge program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.

*/

#ifndef LOGJUDGE_H
#define LOGJUDGE_H

typedef struct entry
{
    int pc;
    int regwrite;
    int regaddr;
    int regdata;
    int memwrite;
    int memaddr;
    int memdata;
} Entry;

#define VERSION "0.2"

#define MAXLN (500)

#define OUT_DIR "out"

#endif  // LOGJUDGE_H
