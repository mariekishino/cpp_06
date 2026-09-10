class Ival_box{
	protected:
		int val;
		int low, high;
		bool changed {false};
	public:
		Ival_box(int ll, int hh) : val{ll}, low{ll}, high{hh} {}

		virtual int get_value() { changed = false; return val; } // アプリケーション用
 		virtual void set_value(int i) { changed = true; val = i;} // ユーザ用
		virtual void reset_value(int i) { changed = false; val = i;} // アプリケーション用
		virtual void prompt() {}
		virtual bool was_changed() const { return changed; }

		virtual ~Ival_box();
};

void interact(Ival_box *pb)
{
	int old_val = pb->get_value();
	pb->prompt();
	int i = pb->get_value();
	if (i != old_val)
	{
		// 新しい値、何らかの処理を行う
	}
	else
	{
		// 別の何らかの処理を行う
	}
}

void some_fct()
{
	unique_ptr<Ival_box> p1 {new Ival_slider{0,5}};
	interact(p1.get());
	unique_ptr<Ival_box> p2 {new Ival_dial{1, 12}};
	interact(p2.get());
}


/* 各種のIval_boxはIval_boxから派生するクラスとして定義する*/

class Ival_slider : public Ival_box
{
	private:
		//
	public:
		Ival_slider(int, int);
		int get_value() override; // ユーザからの値を取り出してvalに格納
		void prompt() override;
}