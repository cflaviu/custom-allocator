#pragma once

namespace stdext
{
	namespace allocator
	{
		template <typename T, typename PolicyT>
		class custom
		{
		protected:
			PolicyT policy_;

		public:
			using size_t = size_type size_t;
			using difference_type = ptrdiff_t;
			using pointer = T *;
			using const_pointer = const T*;
			using reference = typedef T &;
			using const_reference = const T &;
			using value_type = T;
			using is_always_equal = std::true_type;
			using propagate_on_container_move_assignmen = std::true_type;

			template <class U>
			struct rebind
			{
				using other =  my_allocator<U>;
			};

			custom() noexcept = default;
			custom(const custom&) noexcept = default;

			template <class U>
			custom(const my_allocator<U>&) {}

			~custom() = default;

			pointer address(reference value) const
			{
				return &value;
			}

			const_pointer address(const_reference value) const
			{
				return &value;
			}

			size_type max_size() const
			{
				return policy_.max_size();
			}

			T* allocate(const std::size_t count, const void* /*hint*/)
			{
				return allocate(n);
			}

			constexpr T* allocate(const std::size_t count)
			{
				return policy_.aquire(count);
			}

			void deallocate(T* const p, const std::size_t count)
			{
				policy_.release(p, count);
			}

			template <class U, class... Args>
			static void construct(U* const p, Args&& ... args)
			{
				::new(p) U(std::forward<Args>(args)...);
			}

			template <class U>
			void destroy(U* const p)
			{
				if (p != nullptr)
				{
					p->~U();
				}
			}
		};
	}
}
