#pragma once
#include "builder.h"
#include "clike_language.h"

namespace shader_code
{
	enum predefined_function_class_t
	{
		predefined_function_texture_fetch,
		predefined_function_texture_bias_fetch,
		predefined_function_texture_lod_fetch,
		predefined_function_texture_proj_fetch,
		predefined_function_texture_grad_fetch
	};

	template<predefined_function_class_t Function>
	struct predefined_function_name_t;

	template<>
	struct predefined_function_name_t<predefined_function_class_t::predefined_function_texture_fetch>
	{
		static constexpr auto name = "texture_fetch";
	};

	template<>
	struct predefined_function_name_t<predefined_function_class_t::predefined_function_texture_bias_fetch>
	{
		static constexpr auto name = "texture_bias_fetch";
	};

	template<>
	struct predefined_function_name_t<predefined_function_class_t::predefined_function_texture_lod_fetch>
	{
		static constexpr auto name = "texture_lod_fetch";
	};

	template<>
	struct predefined_function_name_t<predefined_function_class_t::predefined_function_texture_proj_fetch>
	{
		static constexpr auto name = "texture_proj_fetch";
	};

	template<>
	struct predefined_function_name_t<predefined_function_class_t::predefined_function_texture_grad_fetch>
	{
		static constexpr auto name = "texture_grad_fetch";
	};

	template<typename Language>
	struct clike_builder : public clike_language, public builder
	{
		using language = Language;

		template<clike_language::type_class_t Type, int Count>
		struct type_helper_t : public clike_language::type_t<Type, Count>
		{
			using base = typename clike_language::type_t<Type, Count>;

		protected:
			template<clike_language::type_class_t ExprType = Type, int ExprCount = Count>
			using expression_t = typename clike_language::expression_t<ExprType, ExprCount>;

		public:
			static expression_t<> ctor()
			{
				return invoke();
			}

			static expression_t<> ctor(typename clike_language::native_type_t<Type>::type value)
			{
				return invoke(expression_t<Type, 1>(native_type_t<Type>::to_string(value)));
			}

			template<clike_language::type_class_t FromType>
			static expression_t<> ctor(expression_t<FromType> expr)
			{
				return invoke(expr);
			}

			static constexpr const char* name()
			{
				using type_name_t = typename language::template type_name_t<Type, Count>;
				return type_name_t::name;
			}

		protected:
			template<typename... T>
			static expression_t<> invoke(T... exprs)
			{
				return function_t<clike_language::type_t<Type, Count>, typename language::template type_name_t<Type, Count>>::invoke(exprs...);
			}
		};

		template<clike_language::type_class_t Type, int Count>
		struct type_t;

		template<clike_language::type_class_t Type>
		struct type_t<Type, 1> : type_helper_t<Type, 1>
		{
			using type_helper_t<Type, 1>::ctor;
		};

		template<clike_language::type_class_t Type>
		struct type_t<Type, 2> : type_helper_t<Type, 2>
		{
			using base = type_helper_t<Type, 2>;
			using base::ctor;

			template<clike_language::type_class_t FromType>
			static typename base::template expression_t<> ctor(typename base::template expression_t<FromType, 1> expr)
			{
				return base::invoke(expr);
			}

			static typename base::template expression_t<> ctor(typename base::template expression_t<Type, 1> a, typename base::template expression_t<Type, 1> b)
			{
				return base::invoke(a, b);
			}
		};

		template<clike_language::type_class_t Type>
		struct type_t<Type, 3> : type_helper_t<Type, 3>
		{
			using base = type_helper_t<Type, 3>;
			using base::ctor;

			template<clike_language::type_class_t FromType>
			static typename base::template expression_t<> ctor(typename base::template expression_t<FromType, 1> expr)
			{
				return base::invoke(expr);
			}

			static typename base::template expression_t<Type, 3> ctor(typename base::template expression_t<Type, 1> a, typename base::template expression_t<Type, 2> b)
			{
				return base::invoke(a, b);
			}

			static typename base::template expression_t<Type, 3> ctor(typename base::template expression_t<Type, 2> a, typename base::template expression_t<Type, 1> b)
			{
				return base::invoke(a, b);
			}

			static typename base::template expression_t<Type, 3> ctor(typename base::template expression_t<Type, 1> a, typename base::template expression_t<Type, 1> b,
				typename base::template expression_t<Type, 1> c)
			{
				return base::invoke(a, b, c);
			}
		};

		template<clike_language::type_class_t Type>
		struct type_t<Type, 4> : type_helper_t<Type, 4>
		{
			using base = type_helper_t<Type, 4>;
			using base::ctor;

			template<clike_language::type_class_t FromType>
			static typename base::template expression_t<Type, 4> ctor(typename base::template expression_t<FromType, 1> expr)
			{
				return base::template invoke(expr);
			}

			static typename base::template expression_t<Type, 4> ctor(typename base::template expression_t<Type, 1> a, typename base::template expression_t<Type, 3> b)
			{
				return base::template invoke(a, b);
			}
			static typename base::template expression_t<Type, 4> ctor(typename base::template expression_t<Type, 3> a, typename base::template expression_t<Type, 1> b)
			{
				return base::template invoke(a, b);
			}
			static typename base::template expression_t<Type, 4> ctor(typename base::template expression_t<Type, 2> a, typename base::template expression_t<Type, 2> b)
			{
				return base::template invoke(a, b);
			}
			static typename base::template expression_t<Type, 4> ctor(typename base::template expression_t<Type, 1> a, typename base::template expression_t<Type, 1> b,
				typename base::template expression_t<Type, 1> c, typename base::template expression_t<Type, 1> d)
			{
				return base::template invoke(a, b, c, d);
			}
			static typename base::template expression_t<Type, 4> ctor(typename base::template expression_t<Type, 2> a, typename base::template expression_t<Type, 1> b,
				typename base::template expression_t<Type, 1> c)
			{
				return base::template invoke(a, b, c);
			}
			static typename base::template expression_t<Type, 4> ctor(typename base::template expression_t<Type, 1> a, typename base::template expression_t<Type, 2> b,
				typename base::template expression_t<Type, 1> c)
			{
				return base::template invoke(a, b, c);
			}
			static typename base::template expression_t<Type, 4> ctor(typename base::template expression_t<Type, 1> a, typename base::template expression_t<Type, 1> b,
				typename base::template expression_t<Type, 2> c)
			{
				return base::template invoke(a, b, c);
			}
		};

		using sampler1D_t = type_t<clike_language::type_class_t::type_sampler1D, 1>;
		using sampler2D_t = type_t<clike_language::type_class_t::type_sampler2D, 1>;
		using sampler3D_t = type_t<clike_language::type_class_t::type_sampler3D, 1>;

		template<size_t Count>
		using boolean_t = type_t<clike_language::type_class_t::type_bool, Count>;

		template<size_t Count>
		using integer_t = type_t<clike_language::type_class_t::type_int, Count>;

		template<size_t Count>
		using float_point_t = type_t<clike_language::type_class_t::type_float, Count>;

		using void_expr = expression_from<void_t>;
		template<int Count> using float_point_expr = expression_from<float_point_t<Count>>;
		template<int Count> using boolean_expr = expression_from<boolean_t<Count>>;
		template<int Count> using integer_expr = expression_from<integer_t<Count>>;

		static expression_from<float_point_t<4>> texture(const expression_from<sampler1D_t>& texture, const expression_from<float_point_t<1>>& coord)
		{
			return function_t<float_point_t<4>, typename language::template function_name_t<function_class_t::function_texture>>::invoke(texture, coord);
		}

		static expression_from<float_point_t<4>> texture(const expression_from<sampler2D_t>& texture, const expression_from<float_point_t<2>>& coord)
		{
			return function_t<float_point_t<4>, typename language::template function_name_t<function_class_t::function_texture>>::invoke(texture, coord);
		}

		static expression_from<float_point_t<4>> texture_lod(const expression_from<sampler2D_t>& texture, const expression_from<float_point_t<2>>& coord, const expression_from<float_point_t<1>>& lod)
		{
			return function_t<float_point_t<4>, typename language::template function_name_t<function_class_t::function_texture_lod>>::invoke(texture, coord, lod);
		}

		static expression_from<float_point_t<4>> texture_bias(const expression_from<sampler2D_t>& texture, const expression_from<float_point_t<2>>& coord, const expression_from<float_point_t<1>>& bias)
		{
			return function_t<float_point_t<4>, typename language::template function_name_t<function_class_t::function_texture_bias>>::invoke(texture, coord, bias);
		}

		static expression_from<float_point_t<4>> texture_grad(const expression_from<sampler2D_t>& texture, const expression_from<float_point_t<2>>& coord, const expression_from<float_point_t<2>>& ddx, const expression_from<float_point_t<2>>& ddy)
		{
			return function_t<float_point_t<4>, typename language::template function_name_t<function_class_t::function_texture_grad>>::invoke(texture, coord, ddx, ddy);
		}

		static expression_from<float_point_t<4>> texture(const expression_from<sampler3D_t>& texture, const expression_from<float_point_t<3>>& coord)
		{
			return function_t<float_point_t<4>, typename language::template function_name_t<function_class_t::function_texture>>::invoke(texture, coord);
		}

		template<int Count>
		static expression_from<float_point_t<Count>> normalize(const expression_t<clike_language::type_class_t::type_float, Count>& arg)
		{
			return function_t<float_point_t<Count>, typename language::template function_name_t<function_class_t::function_normalize>>::invoke(arg);
		}

		template<int Count>
		static expression_from<float_point_t<Count>> sign(const expression_t<clike_language::type_class_t::type_float, Count>& arg)
		{
			return function_t<float_point_t<Count>, typename language::template function_name_t<function_class_t::function_sign>>::invoke(arg);
		}

		template<int Count>
		static expression_from<float_point_t<Count>> abs(const expression_t<clike_language::type_class_t::type_float, Count>& arg)
		{
			return function_t<float_point_t<Count>, typename language::template function_name_t<function_class_t::function_abs>>::invoke(arg);
		}

		template<int Count>
		static expression_from<integer_t<Count>> abs(const expression_t<clike_language::type_class_t::type_int, Count>& arg)
		{
			return function_t<integer_t<Count>, typename language::template function_name_t<function_class_t::function_abs>>::invoke(arg);
		}

		template<int Count>
		static expression_from<boolean_t<1>> any(const expression_t<clike_language::type_class_t::type_bool, Count>& arg)
		{
			return function_t<boolean_t<1>, typename language::template function_name_t<function_class_t::function_any>>::invoke(arg);
		}

		template<int Count, typename = std::enable_if_t<(Count > 1)>>
		static expression_from<boolean_t<1>> all(const expression_t<clike_language::type_class_t::type_bool, Count>& arg)
		{
			return function_t<boolean_t<1>, typename language::template function_name_t<function_class_t::function_all>>::invoke(arg);
		}

		template<int Count, typename = std::enable_if_t<(Count > 1)>>
		static expression_from<float_point_t<1>> dot(const expression_t<clike_language::type_class_t::type_float, Count>& a, const expression_t<clike_language::type_class_t::type_float, Count>& b)
		{
			return function_t<float_point_t<1>, typename language::template function_name_t<function_class_t::function_dot>>::invoke(a, b);
		}

		template<clike_language::type_class_t Type, int Count>
		static expression_t<Type, Count> min(const expression_t<Type, Count>& a, const expression_t<Type, Count>& b)
		{
			return function_t<type_t<Type, Count>, typename language::template function_name_t<function_class_t::function_min>>::invoke(a, b);
		}

		template<clike_language::type_class_t Type, int Count>
		static expression_t<Type, Count> max(const expression_t<Type, Count>& a, const expression_t<Type, Count>& b)
		{
			return function_t<type_t<Type, Count>, typename language::template function_name_t<function_class_t::function_max>>::invoke(a, b);
		}

		template<clike_language::type_class_t Type, int Count>
		static expression_from<boolean_t<Count>> greater(const expression_t<Type, Count>& a, const expression_t<Type, Count>& b)
		{
			return function_t<boolean_t<Count>, typename language::template function_name_t<function_class_t::function_greater>>::invoke(a, b);
		}

		template<clike_language::type_class_t Type, int Count>
		static expression_from<boolean_t<Count>> less(const expression_t<Type, Count>& a, const expression_t<Type, Count>& b)
		{
			return function_t<boolean_t<Count>, typename language::template function_name_t<function_class_t::function_less>>::invoke(a, b);
		}

		template<clike_language::type_class_t Type, int Count>
		static expression_from<boolean_t<Count>> equal(const expression_t<Type, Count>& a, const expression_t<Type, Count>& b)
		{
			return function_t<boolean_t<Count>, typename language::template function_name_t<function_class_t::function_equal>>::invoke(a, b);
		}

		template<clike_language::type_class_t Type, int Count>
		static expression_from<boolean_t<Count>> greater_equal(const expression_t<Type, Count>& a, const expression_t<Type, Count>& b)
		{
			return function_t<boolean_t<Count>, typename language::template function_name_t<function_class_t::function_greater_equal>>::invoke(a, b);
		}

		template<clike_language::type_class_t Type, int Count>
		static expression_from<boolean_t<Count>> less_equal(const expression_t<Type, Count>& a, const expression_t<Type, Count>& b)
		{
			return function_t<boolean_t<Count>, typename language::template function_name_t<function_class_t::function_less_equal>>::invoke(a, b);
		}

		template<clike_language::type_class_t Type, int Count>
		static expression_from<boolean_t<Count>> not_equal(const expression_t<Type, Count>& a, const expression_t<Type, Count>& b)
		{
			return function_t<boolean_t<Count>, typename language::template function_name_t<function_class_t::function_not_equal>>::invoke(a, b);
		}

		template<int Count>
		static expression_from<float_point_t<Count>> fract(const expression_t<clike_language::type_class_t::type_float, Count>& arg)
		{
			return function_t<float_point_t<Count>, typename language::template function_name_t<function_class_t::function_fract>>::invoke(arg);
		}
		template<int Count>
		static expression_from<float_point_t<Count>> floor(const expression_t<clike_language::type_class_t::type_float, Count>& arg)
		{
			return function_t<float_point_t<Count>, typename language::template function_name_t<function_class_t::function_floor>>::invoke(arg);
		}
		template<int Count>
		static expression_from<float_point_t<Count>> sin(const expression_t<clike_language::type_class_t::type_float, Count>& arg)
		{
			return function_t<float_point_t<Count>, typename language::template function_name_t<function_class_t::function_sin>>::invoke(arg);
		}
		template<int Count>
		static expression_from<float_point_t<Count>> cos(const expression_t<clike_language::type_class_t::type_float, Count>& arg)
		{
			return function_t<float_point_t<Count>, typename language::template function_name_t<function_class_t::function_cos>>::invoke(arg);
		}
		template<int Count>
		static expression_from<float_point_t<Count>> clamp(const expression_t<clike_language::type_class_t::type_float, Count>& a, const expression_t<clike_language::type_class_t::type_float, 1>& b, const expression_t<clike_language::type_class_t::type_float, 1>& c)
		{
			return function_t<float_point_t<Count>, typename language::template function_name_t<function_class_t::function_clamp>>::invoke(a, b, c);
		}
		template<int Count>
		static expression_from<integer_t<Count>> clamp(const expression_t<clike_language::type_class_t::type_int, Count>& a, const expression_t<clike_language::type_class_t::type_int, 1>& b, const expression_t<clike_language::type_class_t::type_int, 1>& c)
		{
			return function_t<integer_t<Count>, typename language::template function_name_t<function_class_t::function_clamp>>::invoke(a, b, c);
		}
		template<int Count>
		static expression_from<float_point_t<Count>> sqrt(const expression_t<clike_language::type_class_t::type_float, Count>& arg)
		{
			return function_t<float_point_t<Count>, typename language::template function_name_t<function_class_t::function_sqrt>>::invoke(arg);
		}
		template<int Count>
		static expression_from<float_point_t<Count>> rsqrt(const expression_t<clike_language::type_class_t::type_float, Count>& arg)
		{
			return function_t<float_point_t<Count>, typename language::template function_name_t<function_class_t::function_rsqrt>>::invoke(arg);
		}
		template<int Count>
		static expression_from<float_point_t<Count>> pow(const expression_t<clike_language::type_class_t::type_float, Count>& a, const expression_t<clike_language::type_class_t::type_float, Count>& b)
		{
			return function_t<float_point_t<Count>, typename language::template function_name_t<function_class_t::function_pow>>::invoke(a, b);
		}
		template<int Count>
		static expression_from<float_point_t<Count>> exp(const expression_t<clike_language::type_class_t::type_float, Count>& arg)
		{
			return function_t<float_point_t<Count>, typename language::template function_name_t<function_class_t::function_exp>>::invoke(arg);
		}
		template<int Count>
		static expression_from<float_point_t<Count>> log(const expression_t<clike_language::type_class_t::type_float, Count>& arg)
		{
			return function_t<float_point_t<Count>, typename language::template function_name_t<function_class_t::function_log>>::invoke(arg);
		}
		template<int Count>
		static expression_from<float_point_t<Count>> exp2(const expression_t<clike_language::type_class_t::type_float, Count>& arg)
		{
			return function_t<float_point_t<Count>, typename language::template function_name_t<function_class_t::function_exp2>>::invoke(arg);
		}
		template<int Count>
		static expression_from<float_point_t<Count>> log2(const expression_t<clike_language::type_class_t::type_float, Count>& arg)
		{
			return function_t<float_point_t<Count>, typename language::template function_name_t<function_class_t::function_log2>>::invoke(arg);
		}
		template<int Count>
		static expression_from<float_point_t<Count>> ddx(const expression_t<clike_language::type_class_t::type_float, Count>& arg)
		{
			return function_t<float_point_t<Count>, typename language::template function_name_t<function_class_t::function_ddx>>::invoke(arg);
		}
		template<int Count>
		static expression_from<float_point_t<Count>> ddy(const expression_t<clike_language::type_class_t::type_float, Count>& arg)
		{
			return function_t<float_point_t<Count>, typename language::template function_name_t<function_class_t::function_ddy>>::invoke(arg);
		}

		static expression_from<integer_t<1>> pack_snorm_4x8(const expression_from<float_point_t<4>>& arg)
		{
			return function_t<integer_t<1>, typename language::template function_name_t<function_class_t::function_pack_snorm_4x8>>::invoke(arg);
		}
		static expression_from<float_point_t<4>> unpack_snorm_4x8(const expression_from<integer_t<1>>& arg)
		{
			return function_t<float_point_t<4>, typename language::template function_name_t<function_class_t::function_unpack_snorm_4x8>>::invoke(arg);
		}

		static expression_from<integer_t<1>> pack_unorm_4x8(const expression_from<float_point_t<4>>& arg)
		{
			return function_t<integer_t<1>, typename language::template function_name_t<function_class_t::function_pack_unorm_4x8>>::invoke(arg);
		}
		static expression_from<float_point_t<4>> unpack_unorm_4x8(const expression_from<integer_t<1>>& arg)
		{
			return function_t<float_point_t<4>, typename language::template function_name_t<function_class_t::function_unpack_unorm_4x8>>::invoke(arg);
		}

		static expression_from<integer_t<1>> pack_snorm_2x16(const expression_from<float_point_t<2>>& arg)
		{
			return function_t<integer_t<1>, typename language::template function_name_t<function_class_t::function_pack_snorm_2x16>>::invoke(arg);
		}
		static expression_from<float_point_t<2>> unpack_snorm_2x16(const expression_from<integer_t<1>>& arg)
		{
			return function_t<float_point_t<2>, typename language::template function_name_t<function_class_t::function_unpack_snorm_2x16>>::invoke(arg);
		}

		static expression_from<integer_t<1>> pack_half_2x16(const expression_from<float_point_t<2>>& arg)
		{
			return function_t<integer_t<1>, typename language::template function_name_t<function_class_t::function_pack_half_2x16>>::invoke(arg);
		}
		static expression_from<float_point_t<2>> unpack_half_2x16(const expression_from<integer_t<1>>& arg)
		{
			return function_t<float_point_t<2>, typename language::template function_name_t<function_class_t::function_unpack_half_2x16>>::invoke(arg);
		}


		//predefined functions
		static expression_from<float_point_t<4>> texture_fetch(const expression_from<integer_t<1>>& texture, const expression_from<float_point_t<4>>& arg0)
		{
			return function_t<float_point_t<4>, predefined_function_name_t<predefined_function_class_t::predefined_function_texture_fetch>>::invoke(texture, arg0);
		}
		static expression_from<float_point_t<4>> texture_bias_fetch(const expression_from<integer_t<1>>& texture, const expression_from<float_point_t<4>>& arg0, const expression_from<float_point_t<1>>& arg1)
		{
			return function_t<float_point_t<4>, predefined_function_name_t<predefined_function_class_t::predefined_function_texture_bias_fetch>>::invoke(texture, arg0, arg1);
		}
		static expression_from<float_point_t<4>> texture_grad_fetch(const expression_from<integer_t<1>>& texture, const expression_from<float_point_t<4>>& arg0, const expression_from<float_point_t<4>>& arg1, const expression_from<float_point_t<4>>& arg2)
		{
			return function_t<float_point_t<4>, predefined_function_name_t<predefined_function_class_t::predefined_function_texture_grad_fetch>>::invoke(texture, arg0, arg1, arg2);
		}
		static expression_from<float_point_t<4>> texture_lod_fetch(const expression_from<integer_t<1>>& texture, const expression_from<float_point_t<4>>& arg0, const expression_from<float_point_t<1>>& arg1)
		{
			return function_t<float_point_t<4>, predefined_function_name_t<predefined_function_class_t::predefined_function_texture_lod_fetch>>::invoke(texture, arg0, arg1);
		}
		static expression_from<float_point_t<4>> texture_proj_fetch(const expression_from<integer_t<1>>& texture, const expression_from<float_point_t<4>>& arg0, const expression_from<float_point_t<1>>& arg1)
		{
			return function_t<float_point_t<4>, predefined_function_name_t<predefined_function_class_t::predefined_function_texture_proj_fetch>>::invoke(texture, arg0, arg1);
		}
	};
}
