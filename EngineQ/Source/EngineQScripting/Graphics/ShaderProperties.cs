using System;
using System.Runtime.CompilerServices;

using EngineQ.Math;

namespace EngineQ
{
	/// <summary>
	/// Wrapper class which enables and simplifies usage of set <see cref="EngineQ.Shader"/>
	/// </summary>
	public sealed class ShaderProperties : EngineQ.Object
	{
		#region Types

		/// <summary>
		/// Wrapper class allowing simple control of <see cref="EngineQ.Shader"/> material properties. Used within <see cref="Renderable"/> to control <see cref="Mesh"/> rendering data.
		/// </summary>
		public class MaterialProperties
		{
			private readonly ShaderProperties parent;

			internal MaterialProperties(ShaderProperties parent)
			{
				this.parent = parent;
			}

			/// <summary>
			/// Value of ambient color of material.
			/// </summary>
			public Vector3f Ambient
			{
				get
				{
					Vector3f value;
					API_GetAmbient(parent.NativeHandle, out value);
					return value;
				}
				set
				{
					API_SetAmbient(parent.NativeHandle, ref value);
				}
			}

			/// <summary>
			/// Value of diffuse color of material.
			/// </summary>
			public Vector3f Diffuse
			{
				get
				{
					Vector3f value;
					API_GetDiffuse(parent.NativeHandle, out value);
					return value;
				}
				set
				{
					API_SetDiffuse(parent.NativeHandle, ref value);
				}
			}

			/// <summary>
			/// Value of specular color of material. 
			/// </summary>
			public Vector3f Specular
			{
				get
				{
					Vector3f value;
					API_GetSpecular(parent.NativeHandle, out value);
					return value;
				}
				set
				{
					API_SetSpecular(parent.NativeHandle, ref value);
				}
			}

			/// <summary>
			/// Indicates shininess of redered <see cref="Mesh"/>
			/// </summary>
			public float Shininess
			{
				get
				{
					float value;
					API_GetShininess(parent.NativeHandle, out value);
					return value;
				}
				set
				{
					API_SetShininess(parent.NativeHandle, value);
				}
			}

			/// <summary>
			/// Diffuse <see cref="Texture"/> that will be read from in time of <see cref="Mesh"/> rendering
			/// </summary>
			public Texture DiffuseTexture
			{
				get
				{
					Texture value;
					API_GetDiffuseTexture(parent.NativeHandle, out value);
					return value;
				}
				set
				{
					API_SetDiffuseTexture(parent.NativeHandle, value);
				}
			}

			/// <summary>
			/// Specular <see cref="Texture"/> that will be read from in time of <see cref="Mesh"/> rendering
			/// </summary>
			public Texture SpecularTexture
			{
				get
				{
					Texture value;
					API_GetSpecularTexture(parent.NativeHandle, out value);
					return value;
				}
				set
				{
					API_SetSpecularTexture(parent.NativeHandle, value);
				}
			}

			/// <summary>
			/// NormalMap <see cref="Texture"/> that will be read from in time of <see cref="Mesh"/> rendering
			/// </summary>
			public Texture NormalTexture
			{
				get
				{
					Texture value;
					API_GetNormalTexture(parent.NativeHandle, out value);
					return value;
				}
				set
				{
					API_SetNormalTexture(parent.NativeHandle, value);
				}
			}
		}

		#endregion

		#region Fields

		private MaterialProperties material;

		#endregion

		#region Properties

		/// <summary>
		/// <see cref="EngineQ.Shader"/> associated with this instance of <see cref="ShaderProperties"/>
		/// </summary>
		public Shader Shader
		{
			get
			{
				Shader shader;
				API_GetShader(this.NativeHandle, out shader);
				return shader;
			}
		}

		/// <summary>
		/// Set of <see cref="ShaderProperty{TPropertyType}"/> representing material data that will be used to render <see cref="Mesh"/>
		/// </summary>
		public MaterialProperties Material
		{
			get
			{
				return this.material;
			}
		}

		#endregion

		#region Methods

		private ShaderProperties()
		{
			this.material = new MaterialProperties(this);
		}

		/// <summary>
		/// Checks if property of given <paramref name="propertyName"/> and <typeparamref name="TPropertyType"/> exists within shader
		/// </summary>
		/// <typeparam name="TPropertyType">Type of property to check</typeparam>
		/// <param name="propertyName">Name of property to check</param>
		/// <returns>true if given property exists within shader</returns>
		public bool HasProperty<TPropertyType>(string propertyName)
		{
			int propertyIndex;
			API_GetPropertyIndex(this.NativeHandle, propertyName, typeof(TPropertyType), out propertyIndex);

			return propertyIndex >= 0;
		}

		/// <summary>
		/// Attempts to get property of given <paramref name="name"/> and <typeparamref name="TPropertyType"/>. In case of failure exception will be thrown.
		/// </summary>
		/// <typeparam name="TPropertyType">Type of <see cref="ShaderProperty{TPropertyType}"/> to retrieve.</typeparam>
		/// <param name="propertyName">Name of <see cref="ShaderProperty{TPropertyType}"/> to retrieve.</param>
		/// <returns><see cref="ShaderProperty{TPropertyType}"/> associated with given <paramref name="name"/>.</returns>
		public ShaderProperty<TPropertyType> GetProperty<TPropertyType>(string propertyName)
		{
			int propertyIndex;
			API_GetPropertyIndex(this.NativeHandle, propertyName, typeof(TPropertyType), out propertyIndex);

			if (propertyIndex < 0)
				throw new ArgumentException($"Shader does not have property {propertyName} of type {typeof(TPropertyType)}");

			return new ShaderProperty<TPropertyType>(propertyIndex);
		}

		/// <summary>
		/// Attempts to get property of given <paramref name="name"/> and <typeparamref name="TPropertyType"/>. In case of failure null will be returned.
		/// </summary>
		/// <typeparam name="TPropertyType">Type of <see cref="ShaderProperty{TPropertyType}"/> to retrieve.</typeparam>
		/// <param name="propertyName">Name of <see cref="ShaderProperty{TPropertyType}"/> to retrieve.</param>
		/// <returns><see cref="ShaderProperty{TPropertyType}"/> associated with given <paramref name="name"/> or null.</returns>
		public ShaderProperty<TPropertyType>? TryGetProperty<TPropertyType>(string propertyName)
		{
			int propertyIndex;
			API_GetPropertyIndex(this.NativeHandle, propertyName, typeof(TPropertyType), out propertyIndex);

			if (propertyIndex < 0)
				return null;

			return new ShaderProperty<TPropertyType>(propertyIndex);
		}

		/// <summary>
		/// Retrievs actual value of given <see cref="ShaderProperty{TPropertyType}"/>.
		/// </summary>
		/// <typeparam name="TPropertyType">Type of selected property.</typeparam>
		/// <param name="property">Property which value will be retrieved.</param>
		/// <returns>Current value of given property.</returns>
		public TPropertyType Get<TPropertyType>(ShaderProperty<TPropertyType> property)
		{
			object value = default(TPropertyType);
			API_Get(this.NativeHandle, property.Index, typeof(TPropertyType), out value);
			return (TPropertyType)value;
		}

		/// <summary>
		/// Sets value of <see cref="ShaderProperty{TPropertyType}"/> to given value.
		/// </summary>
		/// <typeparam name="TPropertyType">Type of selected property.</typeparam>
		/// <param name="property">To this property new value will be assigned.</param>
		/// <param name="value">This value will be assigned to property.</param>
		public void Set<TPropertyType>(ShaderProperty<TPropertyType> property, TPropertyType value)
		{
			object objValue = value;
			API_Set(this.NativeHandle, property.Index, typeof(TPropertyType), ref objValue);
		}

		#endregion


		#region API

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_GetShader(IntPtr handle, out Shader shader);

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_GetPropertyIndex(IntPtr handle, string name, Type type, out int propertyIndex);

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_Get(IntPtr handle, int index, Type type, out object value);

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_Set(IntPtr handle, int index, Type type, ref object value);


		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_GetAmbient(IntPtr handle, out Vector3f ambient);
		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_SetAmbient(IntPtr handle, ref Vector3f ambient);

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_GetDiffuse(IntPtr handle, out Vector3f diffuse);
		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_SetDiffuse(IntPtr handle, ref Vector3f diffuse);

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_GetSpecular(IntPtr handle, out Vector3f specular);
		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_SetSpecular(IntPtr handle, ref Vector3f specular);

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_GetShininess(IntPtr handle, out float shininess);
		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_SetShininess(IntPtr handle, float shininess);

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_GetDiffuseTexture(IntPtr handle, out Texture diffuseTexture);
		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_SetDiffuseTexture(IntPtr handle, Texture diffuseTexture);

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_GetSpecularTexture(IntPtr handle, out Texture specularTexture);
		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_SetSpecularTexture(IntPtr handle, Texture specularTexture);

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_GetNormalTexture(IntPtr handle, out Texture normalTexture);
		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_SetNormalTexture(IntPtr handle, Texture normalTexture);

		#endregion
	}
}
