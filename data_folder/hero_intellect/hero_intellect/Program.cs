using System;
using System.Collections.Generic;
using System.IO;

namespace hero_intellect
{
	public class cell
	{
		public int x;
		public int y;

		public cell (int tx, int ty)
		{
			x = tx;
			y = ty;
		}

		public cell(){

		}
	}

	public class troop
	{
		public int x;
		public int y;
		public string type;
		public int kol;
		public int health;
		public bool is_distance;
	}

	class MainClass
	{
		public static List<troop> All_troop = new List<troop> ();
		public static List<troop> My_troop = new List<troop> ();
		public static List<troop> X_troop = new List<troop> ();
		public static List<troop> X_Dist_attack = new List<troop> ();
		public static List<troop> My_Dist_attack = new List<troop> ();
		public static List<troop> X_Melee_attack = new List<troop> ();
		public static List<troop> My_Melee_attack = new List<troop> ();


		public static int calc_distance (troop t1, troop t2)
		{
			int res;
			if (Math.Abs (t1.x - t2.x) > Math.Abs (t1.y - t2.y)) {
				res = Math.Abs (t1.x - t2.x);
				return res;
			} else {
				res = Math.Abs (t1.y - t2.y);
				return res;
			}
		}

		public static int calc_distance (troop t1, cell t2)
		{
			int res;
			if (Math.Abs (t1.x - t2.x) > Math.Abs (t1.y - t2.y)) {
				res = Math.Abs (t1.x - t2.x);
				return res;
			} else {
				res = Math.Abs (t1.y - t2.y);
				return res;
			}
		}

		public static List<int> calc_distance_for_all_my (troop t)
		{
			List<int> res = new List<int> ();
			for (int i = 0; i < X_troop.Count; i++) {
				int a = calc_distance (t, My_troop [i]);
				res.Add (a);
			}
			return res;
		}

		public static List<int> calc_distance_for_all_X (troop t)
		{
			List<int> res = new List<int> ();
			for (int i = 0; i < X_troop.Count; i++) {
				int a = calc_distance (t, X_troop [i]);
				res.Add (a);
			}
			return res;
		}

		public static List<cell> all_x_cell ()
		{
			List<cell> res = new List<cell> ();

			for (int i = 0; i < X_troop.Count; i++) {
				cell a = new cell (X_troop [i].x, X_troop [i].y);
				res.Add (a);
			}

			return res;
		}

		public static bool cell_is_available (int x, int y)
		{
			cell a = new cell (x, y);
			if (x >= 0 && x < 15 && y >= 0 && y < 10) {
				for (int i = 0; i < all_x_cell().Count; i++) {
					if (all_x_cell () [i] == a) {
						return false;
					}
				}

				return true;
			} else {
				return false;
			}
		}

		public static cell rand_near_cell (int x, int y)
		{
			List<cell> res = new List<cell> ();

			if (cell_is_available (x - 1, y) == true) {
				res.Add (new cell (x - 1, y));
			}

			if (cell_is_available (x + 1, y) == true) {
				res.Add (new cell (x + 1, y));
			}

			if (cell_is_available (x, y - 1) == true) {
				res.Add (new cell (x, y - 1));
			}

			if (cell_is_available (x, y + 1) == true) {
				res.Add (new cell (x, y + 1));
			}

			if (cell_is_available (x - 1, y - 1) == true) {
				res.Add (new cell (x - 1, y - 1));
			}

			if (cell_is_available (x - 1, y - 1) == true) {
				res.Add (new cell (x - 1, y - 1));
			}

			if (cell_is_available (x + 1, y - 1) == true) {
				res.Add (new cell (x + 1, y - 1));
			}

			if (cell_is_available (x - 1, y + 1) == true) {
				res.Add (new cell (x - 1, y + 1));
			}

			if (cell_is_available (x + 1, y + 1) == true) {
				res.Add (new cell (x + 1, y + 1));
			}
			Random r1 = new Random ();
			return res [r1.Next (res.Count)];
		}

		public static List<cell> unit_radius_cell (troop t, int r)
		{
			List<cell> rcell = new List<cell> ();
			for (int i = 0; i < r; i++) {
				if (cell_is_available (t.x - r / 2 - 1 + i, t.y +r / 2 - 1) == true) {
					cell a = new cell (t.x - r / 2 - 1 + i, t.y +r / 2 - 1);
					rcell.Add(a);
				}
			}

			for (int i = 0; i < r-2; i++) {
				if (cell_is_available (t.x - r / 2 - 1, t.y +r / 2 - 1-i) == true) {
					cell a = new cell (t.x - r / 2 - 1, t.y +r / 2 - 1-i);
					rcell.Add(a);
				}
				if (cell_is_available (t.x + r / 2 - 1, t.y +r / 2 - 1-i) == true) {
					cell a = new cell (t.x + r / 2 - 1 + i, t.y +r / 2 - 1);
					rcell.Add(a);
				}
			}

			for (int i = 0; i < r; i++) {
				if (cell_is_available (t.x - r / 2 - 1 + i, t.y -r / 2 - 1) == true) {
					cell a = new cell (t.x - r / 2 - 1 + i, t.y -r / 2 - 1);
					rcell.Add(a);
				}
			}

			return rcell;
		}

		public static void Main (string[] args)
		{

			//начало ввода
			FileStream fs = new FileStream ("input.txt", FileMode.Open);
			StreamReader sr = new StreamReader (fs);

			int kol_unit = Convert.ToInt32 (sr.ReadLine ());

			for (int i = 0; i < kol_unit; i++) {
				troop this_troop = new troop ();

				this_troop.x = Convert.ToInt32 (sr.ReadLine ());
				this_troop.y = Convert.ToInt32 (sr.ReadLine ());
				this_troop.type = sr.ReadLine ();
				this_troop.kol = Convert.ToInt32 (sr.ReadLine ());
				this_troop.health = Convert.ToInt32 (sr.ReadLine ());

				All_troop.Add (this_troop);
			} 

			int kol_my_troop = Convert.ToInt32 (sr.ReadLine ());

			for (int i = 0; i < kol_my_troop; i++) {
				My_troop.Add (All_troop [Convert.ToInt32 (sr.ReadLine ())]);
			}

			int kol_x_troop = Convert.ToInt32 (sr.ReadLine ());

			for (int i = 0; i < kol_x_troop; i++) {
				X_troop.Add (All_troop [Convert.ToInt32 (sr.ReadLine ())]);
			}

			int kol_turn = Convert.ToInt32 (sr.ReadLine ());
			int[] Turn = new int[kol_turn];
			for (int i = 0; i< kol_turn; i++) {
				Turn [i] = Convert.ToInt32 (sr.ReadLine ());
			}

			fs.Close ();
			sr.Close ();

			//конец ввода

			//делим отряды по ближней/дальней атаке
			for (int i = 0; i < X_troop.Count; i++) {
				if (X_troop [i].type == "Pikeman") {
					X_troop [i].is_distance = false;
					X_Melee_attack.Add (X_troop [i]);
				} else {
					X_troop [i].is_distance = true;
					X_Dist_attack.Add (X_troop [i]);
				}
			}

			for (int i = 0; i < My_troop.Count; i++) {
				if (My_troop [i].type == "Pikeman") {
					My_troop [i].is_distance = false;
					My_Melee_attack.Add (My_troop [i]);
				} else {
					My_troop [i].is_distance = true;
					My_Dist_attack.Add (My_troop [i]);
				}
			}

			//мой текущий юнит
			troop My_Сurrent_troop = All_troop [Turn [0]];

			if (My_Сurrent_troop.type == "Pikeman") {
				My_Сurrent_troop.is_distance = false;
			} else {
				My_Сurrent_troop.is_distance = true;
			}
			//ближайший противник

			troop Neariest_X = new troop ();
			int min_distance_for_neariest_X = calc_distance (My_Сurrent_troop, X_troop [0]);

			for (int i = 0; i < X_troop.Count; i++) {
				int this_distance = calc_distance (My_Сurrent_troop, X_troop [i]);

				if (this_distance <= min_distance_for_neariest_X) {
					Neariest_X = X_troop [i];
				}

			}

			troop Weak_X = new troop ();
			int min_health = X_troop [0].health;

			for (int i = 0; i < X_troop.Count; i++) {
				int this_health = X_troop [i].health;
				if (this_health <= min_health) {
					Weak_X = X_troop [i];
				}

			}

				troop Neariest_X_dis_attack = new troop ();
				int min_distance_for_neariest_X_dis_attack = calc_distance (My_Сurrent_troop, X_troop [0]);

				for (int i = 0; i < X_troop.Count; i++) {
					int this_distance = calc_distance (My_Сurrent_troop, X_troop [i]);

					if (this_distance <= min_distance_for_neariest_X_dis_attack && X_troop[i].is_distance == true) {
						Neariest_X_dis_attack = X_troop [i];
					}

				}

				troop Neariest_X_mel_attack = new troop ();
				int min_distance_for_neariest_X_mel_attack = calc_distance (My_Сurrent_troop, X_troop [0]);

				for (int i = 0; i < X_troop.Count; i++) {
					int this_distance = calc_distance (My_Сurrent_troop, X_troop [i]);

					if (this_distance <= min_distance_for_neariest_X_mel_attack && X_troop[i].is_distance == false) {
						Neariest_X_mel_attack = X_troop [i];
					}

				}
			//ТАКТИКА_________________________

				int gx = 0;
				int gy = 0;
				int ax = 0;
				int ay = 0;

				if (My_Сurrent_troop.is_distance == true) {
					List<cell> rcell = unit_radius_cell (Neariest_X, 7);

					int min_dis = calc_distance (My_Сurrent_troop, rcell [0]);
					cell min_dis_cell = new cell();
					min_dis_cell = rcell [0];
					for (int i = 0; i < rcell.Count; i++) {
						if (min_dis >= calc_distance (My_Сurrent_troop, rcell [i])) {
							min_dis_cell = rcell [i];
						}
					}
					gx = min_dis_cell.x;
					gy = min_dis_cell.y;
					ax = Neariest_X.x;
					ay = Neariest_X.y;

				} else {
				if (calc_distance (My_Сurrent_troop, Neariest_X) == 1 || calc_distance (My_Сurrent_troop, Neariest_X) == 2) {
						gx = My_Сurrent_troop.x;
						gy = My_Сurrent_troop.y;
						ax = Neariest_X.x;
						ay = Neariest_X.y;
					} else {
						cell rcell = new cell ();
					rcell = rand_near_cell (Neariest_X_dis_attack.x,Neariest_X_dis_attack.y);
						gx = rcell.x;
						gy = rcell.y;
						ax = Neariest_X_dis_attack.x;
						ay = Neariest_X_dis_attack.y;
					}
				}

			//вывод
			StreamWriter sw2 = new StreamWriter ("output.txt");
			sw2.WriteLine (Convert.ToString (gx) + " " + Convert.ToString (gy) + " " + Convert.ToString (ax) + " " + Convert.ToString (ay));
			sw2.Close ();
		}
	}

}
