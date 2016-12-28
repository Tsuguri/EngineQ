using System.Runtime.CompilerServices;

namespace EngineQ
{
	public static class PrefabGenerator
	{
		#region Methods

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
