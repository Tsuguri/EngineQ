using System.Runtime.CompilerServices;

namespace EngineQ
{
	/// <summary>
	/// Provides utulities for creating custon resources.
	/// </summary>
	public static class PrefabGenerator
	{
		#region Methods

		/// <summary>
		/// Creates capsule mesh with given dimensions.
		/// Center of the capsule lies at (0,0,0) and centers of the hemispheres lie on the Y axis.
		/// </summary>
		/// <param name="height">Distance between two capsule's hemispheres' centers.</param>
		/// <param name="radius">Radius of the hemispheres.</param>
		/// <returns>Mesh of the capsule.</returns>
		public static Mesh GenerateCapsule(float height, float radius)
		{
			Mesh value;
			API_GenerateCapsule(height, radius, out value);
			return value;
		}

		public static Mesh GenerateCube(float side = 1.0f)
		{
			Mesh value;
			API_GenerateCube(side, out value);
			return value;
		}

		public static Mesh GenerateQuad(float side = 1.0f)
		{
			Mesh value;
			API_GenerateQuad(side, out value);
			return value;
		}

		public static Texture GenerateNoiseTexture(int width, int height)
		{
			Texture value;
			API_GenerateNoiseTexture(width, height, out value);
			return value;

		}

		#endregion


		#region API

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_GenerateCapsule(float height, float radius, out Mesh mesh);

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_GenerateCube(float side, out Mesh mesh);

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_GenerateQuad(float side, out Mesh mesh);

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_GenerateNoiseTexture(int width, int height, out Texture texture);

		#endregion
	}
}
