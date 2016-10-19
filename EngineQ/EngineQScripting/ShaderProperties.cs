using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;

namespace EngineQ
{
	public sealed class ShaderProperties : EngineQ.Object
	{
		#region Methods

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
		private static extern void API_GetPropertyIndex(IntPtr handle, string name, Type type, out int propertyIndex);
		

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_Get(IntPtr handle, int index, Type type, out object value);

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_Set(IntPtr handle, int index, Type type, ref object value);

		#endregion
	}
}
