// Player.cs
using System;

public class Player {
	public float x = 0;

	public void Update(float dt) {
		x += 1.0f * dt;
		Console.WriteLine($"x = {x}");
	}
}
