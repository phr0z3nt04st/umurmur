/* Copyright (C) 2009-2011, Martin Johansson <martin@fatbob.nu>
   Copyright (C) 2005-2011, Thorvald Natvig <thorvald@natvig.com>

   All rights reserved.

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions
   are met:

   - Redistributions of source code must retain the above copyright notice,
     this list of conditions and the following disclaimer.
   - Redistributions in binary form must reproduce the above copyright notice,
     this list of conditions and the following disclaimer in the documentation
     and/or other materials provided with the distribution.
   - Neither the name of the Developers nor the names of its contributors may
     be used to endorse or promote products derived from this software without
     specific prior written permission.

   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
   ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
   A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE FOUNDATION OR
   CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
   EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
   PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
   PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
   LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
   NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
   SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
#include <sys/time.h>
#include <stdint.h>
#include <stdio.h>

#include "timer.h"

static uint64_t Timer_now()
{
	struct timeval tv;
	uint64_t e;
	
	gettimeofday(&tv, NULL);
	e = tv.tv_sec * 1000000LL;
	e += tv.tv_usec;
	return e;
}


void Timer_init(etimer_t *t)
{
	*t = Timer_now();
}

bool_t Timer_isElapsed(etimer_t *t, uint64_t us)
{
	if (Timer_elapsed(t) > us) {
		*t += us;
		return true;
	}
	return false;

}

uint64_t Timer_elapsed(etimer_t *t)
{
	return Timer_now() - *t;
}

uint64_t Timer_restart(etimer_t *t)
{
	uint64_t n = Timer_now();
	uint64_t e = n - *t;
	*t = n;
	return e;
}
