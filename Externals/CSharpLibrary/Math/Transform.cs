using System.Runtime.InteropServices;

namespace ONEngine {

	[StructLayout(LayoutKind.Sequential)]
	public struct Transform {
		public Vector3 position;
		public Vector3 rotation;
		public Vector3 scale;

		public Transform(Vector3 position, Vector3 rotation, Vector3 scale) {
			this.position = position;
			this.rotation = rotation;
			this.scale = scale;
		}


	}

}