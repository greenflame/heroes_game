using System;
using System.Collections.Generic;
using System.IO;

namespace hero_intellect
{


	public class cell{
		public int x;
		public int y;
		public cell(int tx,int ty){
			x = tx;
			y = ty;
		}
	}

	public class troop{
		public int x;
		public int y;
		public string type;
		public int kol;
		public int life;

	}


	
	class MainClass
	{
		public static List<troop> All_troop = new List<troop> ();
		public static List<troop> My_troop = new List<troop> ();
		public static List<troop> X_troop = new List<troop> ();


		public static int calc_distance(troop t1, troop t2){
			int res;
			if (Math.Abs (t1.x - t2.x) > Math.Abs (t1.y - t2.y)) {
				res = Math.Abs (t1.x - t2.x);
				return res;
			} else {
				res = Math.Abs (t1.y - t2.y);
				return res;
			}
		}

		public static List<cell> all_x_cell(){
			List<cell> res = new List<cell> ();

			for (int i = 0; i < X_troop.Count; i++) {
				cell a = new cell (X_troop [i].x, X_troop [i].y);
				res.Add (a);
			}

			return res;
		}

		public static bool cell_is_available(int x,int y){
			cell a = new cell (x, y);
			if (x >= 0 && x < 15 && y >= 0 && y < 10) {
				for (int i = 0; i < all_x_cell().Count; i++) {
					if (all_x_cell()[i] == a) {
						return false;
					}
				}

				return true;
			} else {
				return false;
			}
		}

		public static cell rand_near_cell(int x,int y){
			List<cell> res = new List<cell> ();

			if (cell_is_available (x-1,y) == true) {
				res.Add (new cell (x - 1, y));
			}

			if (cell_is_available (x+1,y) == true) {
				res.Add (new cell (x + 1, y));
			}

			if (cell_is_available (x,y-1) == true) {
				res.Add (new cell (x, y-1));
			}

			if (cell_is_available (x,y+1) == true) {
				res.Add (new cell (x, y+1));
			}

			Random r1 = new Random ();




			return res[r1.Next(res.Count)];
		}


		public static void Main (string[] args)
		{





			//начало ввода
			FileStream fs = new FileStream ("input.txt", FileMode.Open);
			StreamReader sr = new StreamReader (fs);

			int kol_unit = Convert.ToInt32(sr.ReadLine());

			for (int i = 0; i < kol_unit; i++) {
				troop this_troop = new troop ();

				this_troop.x = Convert.ToInt32(sr.ReadLine());
				this_troop.y = Convert.ToInt32(sr.ReadLine());
				this_troop.type = sr.ReadLine();
				this_troop.kol = Convert.ToInt32(sr.ReadLine());
				this_troop.life = Convert.ToInt32(sr.ReadLine());

				All_troop.Add (this_troop);
			} 

			int kol_my_troop = Convert.ToInt32(sr.ReadLine());

			for (int i = 0; i < kol_my_troop; i++) {
				My_troop.Add (All_troop [Convert.ToInt32 (sr.ReadLine ())]);
			}

			int kol_x_troop = Convert.ToInt32(sr.ReadLine());

			for (int i = 0; i < kol_x_troop; i++) {
				X_troop.Add (All_troop [Convert.ToInt32 (sr.ReadLine ())]);
			}

			int kol_turn = Convert.ToInt32(sr.ReadLine());
			int[] Turn = new int[kol_turn];
			for (int i = 0; i< kol_turn; i++) {
				Turn[i] = Convert.ToInt32(sr.ReadLine());
			}

			fs.Close ();
			sr.Close ();

			//конец ввода

			//мой текущий юнит
			troop My_Сurrent_troop = All_troop[Turn[0]];

			//ближайший противник

			troop Neariest_X = new troop();
			int min_distance_for_neariest_X = calc_distance(My_Сurrent_troop,X_troop[0]);

			for (int i = 0; i < X_troop.Count; i++) {
				int this_distance =  calc_distance(My_Сurrent_troop,X_troop[i]);

				if (this_distance <= min_distance_for_neariest_X) {
					Neariest_X = X_troop [i];
				}

			}
			//вывод

			StreamWriter sw2 = new StreamWriter ("output.txt");

			//Random r1 = new Random ();
			//int near_cell_count = near_cell (Neariest_X.x, Neariest_X.y).Count;
			cell cell_for_attack = rand_near_cell (Neariest_X.x, Neariest_X.y);
			sw2.WriteLine (Convert.ToString(cell_for_attack.x) + " " + Convert.ToString(cell_for_attack.y) + " " + Convert.ToString(Neariest_X.x) + " " + Convert.ToString(Neariest_X.y));
			sw2.Close ();
		}
	}
}
