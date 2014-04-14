/* 
 * Copyright (c) 2013-2014, Quarkslab
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 
 * - Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.
 * - Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 * - Neither the name of Quarkslab nor the names of its contributors may be used
 * to endorse or promote products derived from this software without specific
 * prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef LEELOO_BITS_PERMUTATION_H
#define LEELOO_BITS_PERMUTATION_H

#include <boost/random.hpp>

namespace leeloo {

template <class Integer>
class bits_permutation
{
public:
	typedef Integer integer_type;
	static constexpr size_t integer_bits = sizeof(Integer)*8;

public:
	bits_permutation()
	{ }

	template <class Engine>
	void init(Engine& rand_eng)
	{
		for (int i = 0; i < integer_bits; i++) {
			_perm[i] = i;
		}
		std::random_shuffle(&_perm[0], &_perm[integer_bits],
		                    [&rand_eng](int n) { return boost::random::detail::generate_uniform_int(rand_eng, (int) 0, n); });
	}

	integer_type operator()(integer_type const v) const
	{
		integer_type ret = 0;
		for (int i = 0; i < integer_bits; i++) {
			ret |= ((v & ((integer_type)1)<<i) >> i) << _perm[i];
		}
		return ret;
	}

private:
	uint8_t _perm[integer_bits];
};

}

#endif
