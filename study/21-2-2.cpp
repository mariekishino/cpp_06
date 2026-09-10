/* インタフェース継承　*/
class Ival_box{
	public:
		virtual int get_value() = 0;
		virtual void set_value(int i ) = 0;
		virtual void reset_value(int i ) = 0;
		virtual void prompt() = 0;
		virtual bool was_changed() const = 0;
		virtual ~Ival_box() {}
};

/* 
- データや単純なメンバ関数をなくした
- 初期化すべきデータがなくなったのでコンストラクタもない
- 派生クラスで定義されることになるデータを適切に後始末できるように仮想デストラクタが追加された
*/



/* Ival_slider */

class Ival_slider : public Ival_box, protected BBwidget {
	private:
		// -- sliderに必要なデータ
	protected:
		// BBwidgetの仮想関数をオーバーライドする関数
		// たとえば、BBwidget::draw(), BBwidget::mouse1hit() etc...
	public :
		Ival_slider(int, int);
		~Ival_slider() override;

		int get_value() override;
		void set_value(int i) override;
		// ...
};

void f(Ival_box* p)
{
	// ...
	delete p;
}

/* Ival_boxの階層 */
class Ival_box{ /*     */};
class Ival_slider
	: public Ival_box, protected BBwidget{/*    */};
class Ival_dial
	: public Ival_box, protected BBwidget {/*   */};
class Flashing_ival_slider
	: public Ival_slider { /*  */};
class Popup_ival_slider
	: public Ival_slider { /*   */};
