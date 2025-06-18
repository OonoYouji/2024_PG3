using System.Runtime.InteropServices;

[StructLayout(LayoutKind.Sequential)]
public struct Vector3 {
	public float x, y, z;

	public Vector3(float _x, float _y, float _z) {
		this.x = _x;
		this.y = _y;
		this.z = _z;
	}
}
