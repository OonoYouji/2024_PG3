using System;
using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;

namespace ONEngine {

	public struct Vector3 {
		public float x, y, z;

		public Vector3(float x, float y, float z) {
			this.x = x;
			this.y = y;
			this.z = z;
		}
	}

	[StructLayout(LayoutKind.Sequential)]
	public class Transform {
		public Vector3 position;
		public Vector3 rotation;
		public Vector3 scale;
	}

	public class ScriptComponent {
		public int entityId;
		internal int nativeEntityId;

		public Transform transform {
			get {
				IntPtr ptr = Internal_GetTransform(nativeEntityId);
				return Marshal.PtrToStructure<Transform>(ptr);
			}
			set {
				Internal_SetTransform(nativeEntityId, ref value);
			}
		}

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern IntPtr Internal_GetTransform(int entityId);


		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void Internal_SetTransform(int entityId, ref Transform transform);


		public virtual void Initialize() {
			// Override this method to add initialization logic
		}

		public virtual void Update() {
			// Override this method to add update logic
		}

	}
}