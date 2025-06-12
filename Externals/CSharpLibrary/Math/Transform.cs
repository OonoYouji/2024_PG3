namespace ONEngine {

	//[StructLayout(LayoutKind.Sequential)]
	public class Transform {
		public Vector3 position;
		public Vector3 rotation;
		public Vector3 scale;

		public Transform() {
			position = new Vector3(0, 0, 0);
			rotation = new Vector3(0, 0, 0);
			scale    = new Vector3(1, 1, 1);
		}

		public Transform(Vector3 position, Vector3 rotation, Vector3 scale) {
			this.position = position;
			this.rotation = rotation;
			this.scale = scale;
		}
	}

}