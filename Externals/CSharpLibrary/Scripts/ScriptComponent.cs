using System;
using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;

namespace ONEngine {

	public class ScriptComponent {
		internal int nativeEntityId = -1;

		public Transform transform {
			get {
				IntPtr ptr = Internal_GetTransform(nativeEntityId);
				return Marshal.PtrToStructure<Transform>(ptr);
			}
			set {
				Internal_SetTransform(nativeEntityId, ref value);
			}
		}

		public int EntityId {
			get {
				if (nativeEntityId == -1) {
					nativeEntityId = CreateEntity();
				}
				return nativeEntityId;
			}
		}

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern int CreateEntity();

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