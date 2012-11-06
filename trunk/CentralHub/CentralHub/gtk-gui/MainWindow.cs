
// This file has been generated by the GUI designer. Do not modify.

public partial class MainWindow
{
	private global::Gtk.VBox vbox3;
	private global::Gtk.HScale hscaleSpeed;
	private global::Gtk.Label label1;
	private global::Gtk.HBox hbox2;
	private global::Gtk.VBox vbox1;
	private global::Gtk.Label label2;
	private global::Gtk.SpinButton spinbuttonSeconds;
	private global::Gtk.Table table7;
	private global::Gtk.Button buttonBackward;
	private global::Gtk.Button buttonForward;
	private global::Gtk.Button buttonLeft;
	private global::Gtk.Button buttonRight;
	private global::Gtk.Button buttonStop;
	private global::Gtk.VBox vbox2;
	private global::Gtk.Label label3;
	private global::Gtk.ComboBoxEntry comboboxPort;
	private global::Gtk.Button buttonLink;
	
	protected virtual void Build ()
	{
		global::Stetic.Gui.Initialize (this);
		// Widget MainWindow
		this.Name = "MainWindow";
		this.Title = global::Mono.Unix.Catalog.GetString ("MainWindow");
		this.WindowPosition = ((global::Gtk.WindowPosition)(4));
		// Container child MainWindow.Gtk.Container+ContainerChild
		this.vbox3 = new global::Gtk.VBox ();
		this.vbox3.Name = "vbox3";
		this.vbox3.Spacing = 6;
		// Container child vbox3.Gtk.Box+BoxChild
		this.hscaleSpeed = new global::Gtk.HScale (null);
		this.hscaleSpeed.CanFocus = true;
		this.hscaleSpeed.Name = "hscaleSpeed";
		this.hscaleSpeed.Adjustment.Lower = -127;
		this.hscaleSpeed.Adjustment.Upper = 127;
		this.hscaleSpeed.Adjustment.PageIncrement = 10;
		this.hscaleSpeed.Adjustment.StepIncrement = 1;
		this.hscaleSpeed.DrawValue = true;
		this.hscaleSpeed.Digits = 0;
		this.hscaleSpeed.ValuePos = ((global::Gtk.PositionType)(3));
		this.vbox3.Add (this.hscaleSpeed);
		global::Gtk.Box.BoxChild w1 = ((global::Gtk.Box.BoxChild)(this.vbox3 [this.hscaleSpeed]));
		w1.Position = 0;
		w1.Expand = false;
		w1.Fill = false;
		// Container child vbox3.Gtk.Box+BoxChild
		this.label1 = new global::Gtk.Label ();
		this.label1.Name = "label1";
		this.label1.LabelProp = global::Mono.Unix.Catalog.GetString ("Velocity");
		this.vbox3.Add (this.label1);
		global::Gtk.Box.BoxChild w2 = ((global::Gtk.Box.BoxChild)(this.vbox3 [this.label1]));
		w2.Position = 1;
		w2.Expand = false;
		w2.Fill = false;
		// Container child vbox3.Gtk.Box+BoxChild
		this.hbox2 = new global::Gtk.HBox ();
		this.hbox2.Name = "hbox2";
		this.hbox2.Spacing = 6;
		// Container child hbox2.Gtk.Box+BoxChild
		this.vbox1 = new global::Gtk.VBox ();
		this.vbox1.Name = "vbox1";
		this.vbox1.Spacing = 6;
		// Container child vbox1.Gtk.Box+BoxChild
		this.label2 = new global::Gtk.Label ();
		this.label2.Name = "label2";
		this.label2.LabelProp = global::Mono.Unix.Catalog.GetString ("Seconds");
		this.vbox1.Add (this.label2);
		global::Gtk.Box.BoxChild w3 = ((global::Gtk.Box.BoxChild)(this.vbox1 [this.label2]));
		w3.Position = 0;
		w3.Expand = false;
		w3.Fill = false;
		// Container child vbox1.Gtk.Box+BoxChild
		this.spinbuttonSeconds = new global::Gtk.SpinButton (0, 240, 1);
		this.spinbuttonSeconds.CanFocus = true;
		this.spinbuttonSeconds.Name = "spinbuttonSeconds";
		this.spinbuttonSeconds.Adjustment.PageIncrement = 10;
		this.spinbuttonSeconds.ClimbRate = 1;
		this.spinbuttonSeconds.Numeric = true;
		this.vbox1.Add (this.spinbuttonSeconds);
		global::Gtk.Box.BoxChild w4 = ((global::Gtk.Box.BoxChild)(this.vbox1 [this.spinbuttonSeconds]));
		w4.Position = 1;
		w4.Expand = false;
		w4.Fill = false;
		this.hbox2.Add (this.vbox1);
		global::Gtk.Box.BoxChild w5 = ((global::Gtk.Box.BoxChild)(this.hbox2 [this.vbox1]));
		w5.Position = 0;
		w5.Expand = false;
		w5.Fill = false;
		// Container child hbox2.Gtk.Box+BoxChild
		this.table7 = new global::Gtk.Table (((uint)(3)), ((uint)(3)), false);
		this.table7.Name = "table7";
		this.table7.RowSpacing = ((uint)(6));
		this.table7.ColumnSpacing = ((uint)(6));
		// Container child table7.Gtk.Table+TableChild
		this.buttonBackward = new global::Gtk.Button ();
		this.buttonBackward.CanFocus = true;
		this.buttonBackward.Name = "buttonBackward";
		this.buttonBackward.UseUnderline = true;
		// Container child buttonBackward.Gtk.Container+ContainerChild
		global::Gtk.Alignment w6 = new global::Gtk.Alignment (0.5F, 0.5F, 0F, 0F);
		// Container child GtkAlignment.Gtk.Container+ContainerChild
		global::Gtk.HBox w7 = new global::Gtk.HBox ();
		w7.Spacing = 2;
		// Container child GtkHBox.Gtk.Container+ContainerChild
		global::Gtk.Image w8 = new global::Gtk.Image ();
		w8.Pixbuf = global::Stetic.IconLoader.LoadIcon (this, "gtk-go-down", global::Gtk.IconSize.Menu);
		w7.Add (w8);
		// Container child GtkHBox.Gtk.Container+ContainerChild
		global::Gtk.Label w10 = new global::Gtk.Label ();
		w10.LabelProp = global::Mono.Unix.Catalog.GetString ("_Backward");
		w10.UseUnderline = true;
		w7.Add (w10);
		w6.Add (w7);
		this.buttonBackward.Add (w6);
		this.table7.Add (this.buttonBackward);
		global::Gtk.Table.TableChild w14 = ((global::Gtk.Table.TableChild)(this.table7 [this.buttonBackward]));
		w14.TopAttach = ((uint)(2));
		w14.BottomAttach = ((uint)(3));
		w14.LeftAttach = ((uint)(1));
		w14.RightAttach = ((uint)(2));
		w14.XOptions = ((global::Gtk.AttachOptions)(4));
		w14.YOptions = ((global::Gtk.AttachOptions)(4));
		// Container child table7.Gtk.Table+TableChild
		this.buttonForward = new global::Gtk.Button ();
		this.buttonForward.CanFocus = true;
		this.buttonForward.Name = "buttonForward";
		this.buttonForward.UseUnderline = true;
		// Container child buttonForward.Gtk.Container+ContainerChild
		global::Gtk.Alignment w15 = new global::Gtk.Alignment (0.5F, 0.5F, 0F, 0F);
		// Container child GtkAlignment.Gtk.Container+ContainerChild
		global::Gtk.HBox w16 = new global::Gtk.HBox ();
		w16.Spacing = 2;
		// Container child GtkHBox.Gtk.Container+ContainerChild
		global::Gtk.Image w17 = new global::Gtk.Image ();
		w17.Pixbuf = global::Stetic.IconLoader.LoadIcon (this, "gtk-go-up", global::Gtk.IconSize.Menu);
		w16.Add (w17);
		// Container child GtkHBox.Gtk.Container+ContainerChild
		global::Gtk.Label w19 = new global::Gtk.Label ();
		w19.LabelProp = global::Mono.Unix.Catalog.GetString ("_Forward");
		w19.UseUnderline = true;
		w16.Add (w19);
		w15.Add (w16);
		this.buttonForward.Add (w15);
		this.table7.Add (this.buttonForward);
		global::Gtk.Table.TableChild w23 = ((global::Gtk.Table.TableChild)(this.table7 [this.buttonForward]));
		w23.LeftAttach = ((uint)(1));
		w23.RightAttach = ((uint)(2));
		w23.XOptions = ((global::Gtk.AttachOptions)(4));
		w23.YOptions = ((global::Gtk.AttachOptions)(4));
		// Container child table7.Gtk.Table+TableChild
		this.buttonLeft = new global::Gtk.Button ();
		this.buttonLeft.CanFocus = true;
		this.buttonLeft.Name = "buttonLeft";
		this.buttonLeft.UseUnderline = true;
		// Container child buttonLeft.Gtk.Container+ContainerChild
		global::Gtk.Alignment w24 = new global::Gtk.Alignment (0.5F, 0.5F, 0F, 0F);
		// Container child GtkAlignment.Gtk.Container+ContainerChild
		global::Gtk.HBox w25 = new global::Gtk.HBox ();
		w25.Spacing = 2;
		// Container child GtkHBox.Gtk.Container+ContainerChild
		global::Gtk.Image w26 = new global::Gtk.Image ();
		w26.Pixbuf = global::Stetic.IconLoader.LoadIcon (this, "gtk-undo", global::Gtk.IconSize.Menu);
		w25.Add (w26);
		// Container child GtkHBox.Gtk.Container+ContainerChild
		global::Gtk.Label w28 = new global::Gtk.Label ();
		w28.LabelProp = global::Mono.Unix.Catalog.GetString ("_Left");
		w28.UseUnderline = true;
		w25.Add (w28);
		w24.Add (w25);
		this.buttonLeft.Add (w24);
		this.table7.Add (this.buttonLeft);
		global::Gtk.Table.TableChild w32 = ((global::Gtk.Table.TableChild)(this.table7 [this.buttonLeft]));
		w32.TopAttach = ((uint)(1));
		w32.BottomAttach = ((uint)(2));
		w32.XOptions = ((global::Gtk.AttachOptions)(4));
		w32.YOptions = ((global::Gtk.AttachOptions)(4));
		// Container child table7.Gtk.Table+TableChild
		this.buttonRight = new global::Gtk.Button ();
		this.buttonRight.CanFocus = true;
		this.buttonRight.Name = "buttonRight";
		this.buttonRight.UseUnderline = true;
		// Container child buttonRight.Gtk.Container+ContainerChild
		global::Gtk.Alignment w33 = new global::Gtk.Alignment (0.5F, 0.5F, 0F, 0F);
		// Container child GtkAlignment.Gtk.Container+ContainerChild
		global::Gtk.HBox w34 = new global::Gtk.HBox ();
		w34.Spacing = 2;
		// Container child GtkHBox.Gtk.Container+ContainerChild
		global::Gtk.Image w35 = new global::Gtk.Image ();
		w35.Pixbuf = global::Stetic.IconLoader.LoadIcon (this, "gtk-redo", global::Gtk.IconSize.Menu);
		w34.Add (w35);
		// Container child GtkHBox.Gtk.Container+ContainerChild
		global::Gtk.Label w37 = new global::Gtk.Label ();
		w37.LabelProp = global::Mono.Unix.Catalog.GetString ("_Right");
		w37.UseUnderline = true;
		w34.Add (w37);
		w33.Add (w34);
		this.buttonRight.Add (w33);
		this.table7.Add (this.buttonRight);
		global::Gtk.Table.TableChild w41 = ((global::Gtk.Table.TableChild)(this.table7 [this.buttonRight]));
		w41.TopAttach = ((uint)(1));
		w41.BottomAttach = ((uint)(2));
		w41.LeftAttach = ((uint)(2));
		w41.RightAttach = ((uint)(3));
		w41.XOptions = ((global::Gtk.AttachOptions)(4));
		w41.YOptions = ((global::Gtk.AttachOptions)(4));
		// Container child table7.Gtk.Table+TableChild
		this.buttonStop = new global::Gtk.Button ();
		this.buttonStop.CanFocus = true;
		this.buttonStop.Name = "buttonStop";
		this.buttonStop.UseUnderline = true;
		// Container child buttonStop.Gtk.Container+ContainerChild
		global::Gtk.Alignment w42 = new global::Gtk.Alignment (0.5F, 0.5F, 0F, 0F);
		// Container child GtkAlignment.Gtk.Container+ContainerChild
		global::Gtk.HBox w43 = new global::Gtk.HBox ();
		w43.Spacing = 2;
		// Container child GtkHBox.Gtk.Container+ContainerChild
		global::Gtk.Image w44 = new global::Gtk.Image ();
		w44.Pixbuf = global::Stetic.IconLoader.LoadIcon (this, "gtk-media-stop", global::Gtk.IconSize.Menu);
		w43.Add (w44);
		// Container child GtkHBox.Gtk.Container+ContainerChild
		global::Gtk.Label w46 = new global::Gtk.Label ();
		w46.LabelProp = global::Mono.Unix.Catalog.GetString ("_Stop");
		w46.UseUnderline = true;
		w43.Add (w46);
		w42.Add (w43);
		this.buttonStop.Add (w42);
		this.table7.Add (this.buttonStop);
		global::Gtk.Table.TableChild w50 = ((global::Gtk.Table.TableChild)(this.table7 [this.buttonStop]));
		w50.TopAttach = ((uint)(1));
		w50.BottomAttach = ((uint)(2));
		w50.LeftAttach = ((uint)(1));
		w50.RightAttach = ((uint)(2));
		w50.XOptions = ((global::Gtk.AttachOptions)(4));
		w50.YOptions = ((global::Gtk.AttachOptions)(4));
		this.hbox2.Add (this.table7);
		global::Gtk.Box.BoxChild w51 = ((global::Gtk.Box.BoxChild)(this.hbox2 [this.table7]));
		w51.Position = 1;
		w51.Expand = false;
		w51.Fill = false;
		// Container child hbox2.Gtk.Box+BoxChild
		this.vbox2 = new global::Gtk.VBox ();
		this.vbox2.Name = "vbox2";
		this.vbox2.Spacing = 6;
		// Container child vbox2.Gtk.Box+BoxChild
		this.label3 = new global::Gtk.Label ();
		this.label3.Name = "label3";
		this.label3.LabelProp = global::Mono.Unix.Catalog.GetString ("Port");
		this.vbox2.Add (this.label3);
		global::Gtk.Box.BoxChild w52 = ((global::Gtk.Box.BoxChild)(this.vbox2 [this.label3]));
		w52.Position = 0;
		w52.Expand = false;
		w52.Fill = false;
		// Container child vbox2.Gtk.Box+BoxChild
		this.comboboxPort = global::Gtk.ComboBoxEntry.NewText ();
		this.comboboxPort.WidthRequest = 100;
		this.comboboxPort.Name = "comboboxPort";
		this.vbox2.Add (this.comboboxPort);
		global::Gtk.Box.BoxChild w53 = ((global::Gtk.Box.BoxChild)(this.vbox2 [this.comboboxPort]));
		w53.Position = 1;
		w53.Expand = false;
		w53.Fill = false;
		// Container child vbox2.Gtk.Box+BoxChild
		this.buttonLink = new global::Gtk.Button ();
		this.buttonLink.CanFocus = true;
		this.buttonLink.Name = "buttonLink";
		this.buttonLink.UseUnderline = true;
		this.buttonLink.Label = global::Mono.Unix.Catalog.GetString ("Link");
		this.vbox2.Add (this.buttonLink);
		global::Gtk.Box.BoxChild w54 = ((global::Gtk.Box.BoxChild)(this.vbox2 [this.buttonLink]));
		w54.Position = 2;
		w54.Expand = false;
		w54.Fill = false;
		this.hbox2.Add (this.vbox2);
		global::Gtk.Box.BoxChild w55 = ((global::Gtk.Box.BoxChild)(this.hbox2 [this.vbox2]));
		w55.Position = 2;
		w55.Expand = false;
		w55.Fill = false;
		this.vbox3.Add (this.hbox2);
		global::Gtk.Box.BoxChild w56 = ((global::Gtk.Box.BoxChild)(this.vbox3 [this.hbox2]));
		w56.Position = 2;
		w56.Expand = false;
		w56.Fill = false;
		this.Add (this.vbox3);
		if ((this.Child != null)) {
			this.Child.ShowAll ();
		}
		this.DefaultWidth = 376;
		this.DefaultHeight = 217;
		this.Show ();
		this.DeleteEvent += new global::Gtk.DeleteEventHandler (this.OnDeleteEvent);
		this.buttonStop.Clicked += new global::System.EventHandler (this.clickStop);
		this.buttonRight.Clicked += new global::System.EventHandler (this.clickRotateRight);
		this.buttonLeft.Clicked += new global::System.EventHandler (this.clickRotateLeft);
		this.buttonForward.Clicked += new global::System.EventHandler (this.clickForward);
		this.buttonBackward.Clicked += new global::System.EventHandler (this.clickBackward);
		this.buttonLink.Clicked += new global::System.EventHandler (this.clickPortLink);
	}
}
