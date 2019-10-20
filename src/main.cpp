#include "pch.h"
#include "object_pool/policy/fixed_size.h"

int main()
{
	object_pool::policy::fixed_size<int, 3> a;
	auto p1 = a.acquire();
	auto p2 = a.acquire();
	auto p3 = a.acquire();
	auto p4 = a.acquire();

	auto& d = a.data_usage();

	a.release(p1);
	a.release(p3);
	a.release(p2);

	return 0;
}
