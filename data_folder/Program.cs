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
		public int id;
		public bool is_my;
		public int x;
		public int y;
		public string type;
		public int kol;
		public int life;

		public List<cell> cell_for_attack(){
			List<cell> res = new List<cell> ();

			if (this.x - 1 >= 0) {
				cell a = new cell(this.x - 1,this.y);
				res.Add (a);
			}

			if (this.x + 1 < 15) {
				cell a = new cell(this.x + 1,this.y);
				res.Add (a);
			}

			if (this.y - 1 >= 0) {
				cell a = new cell(this.x,this.y - 1);
				res.Add (a);
			}

			if (this.y + 1 < 10) {
				cell a = new cell(this.x,this.y + 1);
				res.Add (a);

			}

			return res;
		}
	}

	class MainClass
	{


		public static void Main (string[] args)
		{

			List<troop> My_troop = new List<troop> ();
			List<troop> X_troop = new List<troop> ();

			FileStream fs = new FileStream ("input.txt", FileMode.Open);
			StreamReader sr = new StreamReader (fs);

			int kol_unit = Convert.ToInt32(sr.ReadLine());

			for (int i = 0; i < kol_unit; i++) {
				troop this_troop = new troop ();
				this_troop.id = Convert.ToInt32(sr.ReadLine());

				if (sr.ReadLine () == "anton") {
					this_troop.is_my = true;
				} else {
					this_troop.is_my = false;
				}

				this_troop.x = Convert.ToInt32(sr.ReadLine());
				this_troop.y = Convert.ToInt32(sr.ReadLine());
				this_troop.type = sr.ReadLine();
				this_troop.kol = Convert.ToInt32(sr.ReadLine());
				this_troop.life = Convert.ToInt32(sr.ReadLine());

				if (this_troop.is_my == true) {
					My_troop.Add (this_troop);
				} else {
					X_troop.Add (this_troop);
				}
			} 

			int kol_step = Convert.ToInt32(sr.ReadLine());
			int[] Step = new int[kol_step];
			for (int i = 0; i< kol_step; i++) {
				Step[i] = Convert.ToInt32(sr.ReadLine());
			}

			fs.Close ();
			sr.Close ();

			//конец ввода

			//мой текущий юнит
			troop My_Сurrent_troop = new troop();

			for (int i = 0; i < My_troop.Count; i++) {
				if (My_troop[i].id == Step [0]) {
					My_Сurrent_troop = My_troop [i];
					break;
				}
			}

			//ближайший противник

			troop Neariest_X = new troop();
			int min_distance_for_neariest_X;

			if (Math.Abs (My_Сurrent_troop.x - X_troop [0].x) > Math.Abs (My_Сurrent_troop.y - X_troop [0].y)) {
				min_distance_for_neariest_X = Math.Abs (My_Сurrent_troop.x - X_troop [0].x);
			} else {
				min_distance_for_neariest_X = Math.Abs (My_Сurrent_troop.y - X_troop [0].y);
			}

			for (int i = 0; i < X_troop.Count; i++) {
				int this_distance;

				if (Math.Abs (My_Сurrent_troop.x - X_troop [i].x) > Math.Abs (My_Сurrent_troop.y - X_troop [i].y)) {
					this_distance = Math.Abs (My_Сurrent_troop.x - X_troop [i].x);
				} else {
					this_distance = Math.Abs (My_Сurrent_troop.y - X_troop [i].y);
				}

				if (this_distance <= min_distance_for_neariest_X) {
					Neariest_X = X_troop [i];
				}

			}
			//подготовка output

			StreamWriter sw2 = new StreamWriter ("output.txt");

			Random r1 = new Random ();
			cell cell_for_attack = Neariest_X.cell_for_attack ()[r1.Next(Neariest_X.cell_for_attack ().Count)];
			sw2.WriteLine (Convert.ToString(cell_for_attack.x) + " " + Convert.ToString(cell_for_attack.y) + " " + Convert.ToString(Neariest_X.x) + " " + Convert.ToString(Neariest_X.y));
			sw2.Close ();
		}
	}
}
