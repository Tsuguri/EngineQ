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
			Mesh mesh;
			API_GenerateCapsule(height, radius, out mesh);
			return mesh;
		}

		#endregion


		#region API

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void API_GenerateCapsule(float height, float radius, out Mesh mesh);

		#endregion
	}
}
