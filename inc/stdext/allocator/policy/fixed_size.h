#pragma once

namespace stdext
{
	namespace allocator
	{
		namespace policy
		{
			template <typename T, size_t SizeT>
			class fixed_size
			{
			public:
				using storage = typename std::aligned_storage<sizeof(T), alignof(T)>::type;
				using usage = std::array<bool, SizeT>;

				fixed_size() = default;
				fixed_size(const fixed_size&) = delete;
				~fixed_size() = default;

				const usage& data_usage() const { return data_usage_; }

				T* data() { return reinterpret_cast<T*>(&data_); }
				const T* data() const { return reinterpret_cast<const T*>(&data_); }

				constexpr size_t max_size() const { return SizeT; }

				T* acquire()
				{
					auto item = std::find(data_usage_.begin(), data_usage_.end(), false);
					if (item != data_usage_.end())
					{
						*item = true;
						return data() + std::distance(data_usage_.begin(), item);
					}

					return nullptr;
				}

				T* acquire(const size_t count)
				{
					auto item = std::search_n(data_usage_.begin(), data_usage_.end(), count, false);
					if (item != data_usage_.end())
					{
						std::fill_n(item, count, true);
						return data() + std::distance(data_usage_.begin(), item);
					}

					return nullptr;
				}

				void release(T* const item, const size_t count = 1)
				{
					auto index = static_cast<size_t>(std::distance(data(), item));
					if (index + count <= size())
					{
						std::fill_n(data_usage_.begin() + index, count, false);
					}
				}

			protected:
				usage data_usage_ = { false };
				storage data_[max_size()];
			};
		}
	}
}
