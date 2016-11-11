using System;
using System.Runtime.CompilerServices;

using EngineQ.Math;

namespace EngineQ
{
	public sealed class ShaderProperties : EngineQ.Object
	{
		#region Types

		public class MaterialProperties
		{
			private readonly ShaderProperties parent;

			internal MaterialProperties(ShaderProperties parent)
			{
				this.parent = parent;
			}

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

		public Shader Shader
		{
			get
			{
				Shader shader;
				API_GetShader(this.NativeHandle, out shader);
				return shader;
			}
		}

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

		public bool HasProperty<TPropertyType>(string propertyName)
		{
			int propertyIndex;
			API_GetPropertyIndex(this.NativeHandle, propertyName, typeof(TPropertyType), out propertyIndex);

			return propertyIndex >= 0;
		}

		public ShaderProperty<TPropertyType> GetProperty<TPropertyType>(string propertyName)
		{
			int propertyIndex;
			API_GetPropertyIndex(this.NativeHandle, propertyName, typeof(TPropertyType), out propertyIndex);

			if (propertyIndex < 0)
				throw new ArgumentException($"Shader does not have property {propertyName} of type {typeof(TPropertyType)}");

			return new ShaderProperty<TPropertyType>(propertyIndex);
		}

		public ShaderProperty<TPropertyType>? TryGetProperty<TPropertyType>(string propertyName)
		{
			int propertyIndex;
			API_GetPropertyIndex(this.NativeHandle, propertyName, typeof(TPropertyType), out propertyIndex);

			if (propertyIndex < 0)
				return null;

			return new ShaderProperty<TPropertyType>(propertyIndex);
		}

		public TPropertyType Get<TPropertyType>(ShaderProperty<TPropertyType> property)
		{
			object value = default(TPropertyType);
			API_Get(this.NativeHandle, property.Index, typeof(TPropertyType), out value);
			return (TPropertyType)value;
		}

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
