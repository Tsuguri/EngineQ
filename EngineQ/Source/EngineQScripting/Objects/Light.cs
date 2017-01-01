using EngineQ.Math;

namespace EngineQ
{
	/// <summary>
	/// Type of the <see cref="Light"/> component.
	/// </summary>
	public enum LightType
	{
		Sun,
		Point,
		Spotlight,
	}

	/// <summary>
	/// <see cref="Component"/> providing light functionality for the <see cref="Entity"/>.
	/// </summary>
	public sealed class Light : Component
	{
		#region Properties

		/// <summary>
		/// Ambient color of the light.
		/// </summary>
		public Vector3 AmbientColor
		{
			get
			{
				throw new System.NotImplementedException();
			}
			set
			{
				throw new System.NotImplementedException();
			}
		}

		/// <summary>
		/// Diffuse color of the light.
		/// </summary>
		public Vector3 DiffuseColor
		{
			get
			{
				throw new System.NotImplementedException();
			}
			set
			{
				throw new System.NotImplementedException();
			}
		}

		/// <summary>
		/// Specular color of the light.
		/// </summary>
		public Vector3 SpecularColor
		{
			get
			{
				throw new System.NotImplementedException();
			}
			set
			{
				throw new System.NotImplementedException();
			}
		}

		/// <summary>
		/// Type of the light.
		/// </summary>
		public LightType Type
		{
			get
			{
				throw new System.NotImplementedException();
			}
			set
			{
				throw new System.NotImplementedException();
			}
		}

		/// <summary>
		/// Specifies whether light casts shadows.
		/// </summary>
		public bool CastShadows
		{
			get
			{
				throw new System.NotImplementedException();
			}
			set
			{
				throw new System.NotImplementedException();
			}
		}
		
		/// <summary>
		/// Range of the light.
		/// </summary>
		public float Distance
		{
			get
			{
				throw new System.NotImplementedException();
			}
			set
			{
				throw new System.NotImplementedException();
			}
		}

		#endregion
	}
}
