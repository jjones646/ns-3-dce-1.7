/*
 * gVirtuS -- A GPGPU transparent virtualization component.
 *
 * Copyright (C) 2009-2010  The University of Napoli Parthenope at Naples.
 *
 * This file is part of gVirtuS.
 *
 * gVirtuS is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * gVirtuS is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with gVirtuS; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 * Written by: Giuseppe Coviello <giuseppe.coviello@uniparthenope.it>,
 *             Department of Applied Science
 */

/**
 * @file   Communicator.cpp
 * @author Giuseppe Coviello <giuseppe.coviello@uniparthenope.it>
 * @date   Wed Sep 30 11:56:44 2009
 *
 * @brief
 *
 *
 */

#include "cuda-communicator.h"

#include <cstring>
#include <cstdlib>

#include "dce-tap-communicator.h"
#include "dce-unix-communicator.h"

using namespace std;

Communicator * Communicator::Get(const std::string & communicator)
{
    const char *s = communicator.c_str();
    const char *tmp = strstr(s, "://");
    if (tmp == NULL)
        throw "Invalid communicator string.";
    char *type = new char[tmp - s + 1];
    memmove(type, s, tmp - s);
    type[tmp - s] = 0;
    if (strcmp(type, "tap") == 0)
        return new DceTapCommunicator(communicator);
    if (strcmp(type, "afunix") == 0)
        return new DceUnixCommunicator(communicator);
    throw "Not a valid communicator type!";
    return NULL;
}

Communicator::~Communicator()
{
}

