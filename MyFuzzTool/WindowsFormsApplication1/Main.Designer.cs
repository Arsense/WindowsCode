namespace MyFuzzTool
{
   
    partial class frmFileFuzz
    {
        /// <summary>
        /// 必需的设计器变量。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 清理所有正在使用的资源。
        /// </summary>
        /// <param name="disposing">如果应释放托管资源，为 true；否则为 false。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows 窗体设计器生成的代码

        /// <summary>
        /// 设计器支持所需的方法 - 不要修改
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(frmFileFuzz));
            this.lblFileType = new System.Windows.Forms.Label();
            this.cbxFileType = new System.Windows.Forms.ComboBox();
            this.cbxStripFileExt = new System.Windows.Forms.CheckBox();
            this.checkBox2 = new System.Windows.Forms.CheckBox();
            this.tclMain = new System.Windows.Forms.TabControl();
            this.create = new System.Windows.Forms.TabPage();
            this.tbxSourceFile1 = new System.Windows.Forms.TextBox();
            this.tbxTargetDirectory = new System.Windows.Forms.TextBox();
            this.gbxTarget = new System.Windows.Forms.GroupBox();
            this.lblTargetBytesMultiple = new System.Windows.Forms.Label();
            this.tbxTargetBytesNumber = new System.Windows.Forms.TextBox();
            this.tbxTargetByte = new System.Windows.Forms.TextBox();
            this.tbxTargetByteFinish = new System.Windows.Forms.TextBox();
            this.lbltbxTargetBytes = new System.Windows.Forms.Label();
            this.gbxScope = new System.Windows.Forms.GroupBox();
            this.lblRegexReplace = new System.Windows.Forms.Label();
            this.lblRegexFind = new System.Windows.Forms.Label();
            this.lblRangeStart = new System.Windows.Forms.Label();
            this.rbtRegex = new System.Windows.Forms.RadioButton();
            this.rbtDepth = new System.Windows.Forms.RadioButton();
            this.rbtRange = new System.Windows.Forms.RadioButton();
            this.rbtAllBytes = new System.Windows.Forms.RadioButton();
            this.lblTargetDirectory = new System.Windows.Forms.Label();
            this.lblSourceFile = new System.Windows.Forms.Label();
            this.execute = new System.Windows.Forms.TabPage();
            this.tbxCount = new System.Windows.Forms.TextBox();
            this.tbxMilliseconds = new System.Windows.Forms.TextBox();
            this.tbxFinishFile = new System.Windows.Forms.TextBox();
            this.tbxStartFile = new System.Windows.Forms.TextBox();
            this.lblCount = new System.Windows.Forms.Label();
            this.lblMilliseconds = new System.Windows.Forms.Label();
            this.lblFinishFile = new System.Windows.Forms.Label();
            this.lblStartFile = new System.Windows.Forms.Label();
            this.lblExecuteArgs = new System.Windows.Forms.Label();
            this.tbxExecuteArgs = new System.Windows.Forms.TextBox();
            this.tbxExecuteApp = new System.Windows.Forms.TextBox();
            this.lblExecuteApp = new System.Windows.Forms.Label();
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.mnuFile = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuFileExit = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuEdit = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuEditCopy = new System.Windows.Forms.ToolStripMenuItem();
            this.button1 = new System.Windows.Forms.Button();
            this.btnSourceFile = new System.Windows.Forms.Button();
            this.button3 = new System.Windows.Forms.Button();
            this.btnTargetDirectory = new System.Windows.Forms.Button();
            this.btnCreateFiles = new System.Windows.Forms.Button();
            this.ofdSourceFile = new System.Windows.Forms.OpenFileDialog();
            this.fbdTargetDirectory = new System.Windows.Forms.FolderBrowserDialog();
            this.tclMain.SuspendLayout();
            this.create.SuspendLayout();
            this.gbxTarget.SuspendLayout();
            this.gbxScope.SuspendLayout();
            this.execute.SuspendLayout();
            this.menuStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // lblFileType
            // 
            this.lblFileType.AutoSize = true;
            this.lblFileType.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.lblFileType.Location = new System.Drawing.Point(12, 32);
            this.lblFileType.Name = "lblFileType";
            this.lblFileType.Size = new System.Drawing.Size(74, 20);
            this.lblFileType.TabIndex = 0;
            this.lblFileType.Text = "File Type";
            this.lblFileType.TextAlign = System.Drawing.ContentAlignment.TopCenter;
            // 
            // cbxFileType
            // 
            this.cbxFileType.Location = new System.Drawing.Point(122, 32);
            this.cbxFileType.Name = "cbxFileType";
            this.cbxFileType.Size = new System.Drawing.Size(243, 23);
            this.cbxFileType.TabIndex = 24;
            // 
            // cbxStripFileExt
            // 
            this.cbxStripFileExt.Location = new System.Drawing.Point(385, 32);
            this.cbxStripFileExt.Name = "cbxStripFileExt";
            this.cbxStripFileExt.Size = new System.Drawing.Size(215, 24);
            this.cbxStripFileExt.TabIndex = 25;
            this.cbxStripFileExt.Text = "Strip File Extension";
            this.cbxStripFileExt.UseVisualStyleBackColor = true;
            // 
            // checkBox2
            // 
            this.checkBox2.AutoSize = true;
            this.checkBox2.Location = new System.Drawing.Point(593, 34);
            this.checkBox2.Name = "checkBox2";
            this.checkBox2.Size = new System.Drawing.Size(221, 19);
            this.checkBox2.TabIndex = 26;
            this.checkBox2.Text = "Exclude Target Directory";
            this.checkBox2.UseVisualStyleBackColor = true;
            // 
            // tclMain
            // 
            this.tclMain.Appearance = System.Windows.Forms.TabAppearance.FlatButtons;
            this.tclMain.Controls.Add(this.create);
            this.tclMain.Controls.Add(this.execute);
            this.tclMain.HotTrack = true;
            this.tclMain.Location = new System.Drawing.Point(12, 94);
            this.tclMain.Name = "tclMain";
            this.tclMain.SelectedIndex = 0;
            this.tclMain.Size = new System.Drawing.Size(790, 458);
            this.tclMain.SizeMode = System.Windows.Forms.TabSizeMode.Fixed;
            this.tclMain.TabIndex = 27;
            // 
            // create
            // 
            this.create.Controls.Add(this.tbxSourceFile1);
            this.create.Controls.Add(this.tbxTargetDirectory);
            this.create.Controls.Add(this.gbxTarget);
            this.create.Controls.Add(this.gbxScope);
            this.create.Controls.Add(this.lblTargetDirectory);
            this.create.Controls.Add(this.lblSourceFile);
            this.create.Location = new System.Drawing.Point(4, 28);
            this.create.Name = "create";
            this.create.Padding = new System.Windows.Forms.Padding(3);
            this.create.Size = new System.Drawing.Size(782, 426);
            this.create.TabIndex = 0;
            this.create.Text = "Create";
            // 
            // tbxSourceFile1
            // 
            this.tbxSourceFile1.Location = new System.Drawing.Point(31, 63);
            this.tbxSourceFile1.Name = "tbxSourceFile1";
            this.tbxSourceFile1.Size = new System.Drawing.Size(745, 25);
            this.tbxSourceFile1.TabIndex = 6;
            this.tbxSourceFile1.TextChanged += new System.EventHandler(this.textBox8_TextChanged);
            // 
            // tbxTargetDirectory
            // 
            this.tbxTargetDirectory.Location = new System.Drawing.Point(31, 140);
            this.tbxTargetDirectory.Name = "tbxTargetDirectory";
            this.tbxTargetDirectory.Size = new System.Drawing.Size(745, 25);
            this.tbxTargetDirectory.TabIndex = 5;
            // 
            // gbxTarget
            // 
            this.gbxTarget.Controls.Add(this.lblTargetBytesMultiple);
            this.gbxTarget.Controls.Add(this.tbxTargetBytesNumber);
            this.gbxTarget.Controls.Add(this.tbxTargetByte);
            this.gbxTarget.Controls.Add(this.tbxTargetByteFinish);
            this.gbxTarget.Controls.Add(this.lbltbxTargetBytes);
            this.gbxTarget.Location = new System.Drawing.Point(23, 203);
            this.gbxTarget.Name = "gbxTarget";
            this.gbxTarget.Size = new System.Drawing.Size(267, 170);
            this.gbxTarget.TabIndex = 1;
            this.gbxTarget.TabStop = false;
            this.gbxTarget.Text = "Target";
            // 
            // lblTargetBytesMultiple
            // 
            this.lblTargetBytesMultiple.Font = new System.Drawing.Font("微软雅黑", 10.8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.lblTargetBytesMultiple.Location = new System.Drawing.Point(133, 98);
            this.lblTargetBytesMultiple.Name = "lblTargetBytesMultiple";
            this.lblTargetBytesMultiple.Size = new System.Drawing.Size(57, 22);
            this.lblTargetBytesMultiple.TabIndex = 32;
            this.lblTargetBytesMultiple.Text = "X";
            this.lblTargetBytesMultiple.TextAlign = System.Drawing.ContentAlignment.TopCenter;
            // 
            // tbxTargetBytesNumber
            // 
            this.tbxTargetBytesNumber.Location = new System.Drawing.Point(138, 139);
            this.tbxTargetBytesNumber.Name = "tbxTargetBytesNumber";
            this.tbxTargetBytesNumber.Size = new System.Drawing.Size(84, 25);
            this.tbxTargetBytesNumber.TabIndex = 31;
            this.tbxTargetBytesNumber.Text = "4";
            // 
            // tbxTargetByte
            // 
            this.tbxTargetByte.Location = new System.Drawing.Point(138, 24);
            this.tbxTargetByte.Name = "tbxTargetByte";
            this.tbxTargetByte.Size = new System.Drawing.Size(42, 25);
            this.tbxTargetByte.TabIndex = 30;
            // 
            // tbxTargetByteFinish
            // 
            this.tbxTargetByteFinish.Location = new System.Drawing.Point(138, 70);
            this.tbxTargetByteFinish.Name = "tbxTargetByteFinish";
            this.tbxTargetByteFinish.Size = new System.Drawing.Size(42, 25);
            this.tbxTargetByteFinish.TabIndex = 30;
            this.tbxTargetByteFinish.Text = "FF";
            // 
            // lbltbxTargetBytes
            // 
            this.lbltbxTargetBytes.Font = new System.Drawing.Font("微软雅黑", 10.8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.lbltbxTargetBytes.Location = new System.Drawing.Point(6, 21);
            this.lbltbxTargetBytes.Name = "lbltbxTargetBytes";
            this.lbltbxTargetBytes.Size = new System.Drawing.Size(126, 58);
            this.lbltbxTargetBytes.TabIndex = 29;
            this.lbltbxTargetBytes.Text = "Byte(s) to Overwrite";
            this.lbltbxTargetBytes.TextAlign = System.Drawing.ContentAlignment.BottomCenter;
            // 
            // gbxScope
            // 
            this.gbxScope.Controls.Add(this.lblRegexReplace);
            this.gbxScope.Controls.Add(this.lblRegexFind);
            this.gbxScope.Controls.Add(this.lblRangeStart);
            this.gbxScope.Controls.Add(this.rbtRegex);
            this.gbxScope.Controls.Add(this.rbtDepth);
            this.gbxScope.Controls.Add(this.rbtRange);
            this.gbxScope.Controls.Add(this.rbtAllBytes);
            this.gbxScope.Font = new System.Drawing.Font("幼圆", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.gbxScope.Location = new System.Drawing.Point(339, 203);
            this.gbxScope.Name = "gbxScope";
            this.gbxScope.Size = new System.Drawing.Size(365, 202);
            this.gbxScope.TabIndex = 4;
            this.gbxScope.TabStop = false;
            this.gbxScope.Text = "Scope";
            // 
            // lblRegexReplace
            // 
            this.lblRegexReplace.AutoSize = true;
            this.lblRegexReplace.Font = new System.Drawing.Font("微软雅黑", 9F, ((System.Drawing.FontStyle)((System.Drawing.FontStyle.Bold | System.Drawing.FontStyle.Italic))), System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.lblRegexReplace.Location = new System.Drawing.Point(152, 155);
            this.lblRegexReplace.Name = "lblRegexReplace";
            this.lblRegexReplace.Size = new System.Drawing.Size(68, 19);
            this.lblRegexReplace.TabIndex = 7;
            this.lblRegexReplace.Text = "Replace";
            this.lblRegexReplace.TextAlign = System.Drawing.ContentAlignment.BottomLeft;
            // 
            // lblRegexFind
            // 
            this.lblRegexFind.AutoSize = true;
            this.lblRegexFind.Font = new System.Drawing.Font("微软雅黑", 9F, ((System.Drawing.FontStyle)((System.Drawing.FontStyle.Bold | System.Drawing.FontStyle.Italic))), System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.lblRegexFind.Location = new System.Drawing.Point(152, 113);
            this.lblRegexFind.Name = "lblRegexFind";
            this.lblRegexFind.Size = new System.Drawing.Size(41, 19);
            this.lblRegexFind.TabIndex = 6;
            this.lblRegexFind.Text = "Find";
            this.lblRegexFind.TextAlign = System.Drawing.ContentAlignment.BottomLeft;
            // 
            // lblRangeStart
            // 
            this.lblRangeStart.AutoSize = true;
            this.lblRangeStart.Font = new System.Drawing.Font("微软雅黑", 9F, ((System.Drawing.FontStyle)((System.Drawing.FontStyle.Bold | System.Drawing.FontStyle.Italic))), System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.lblRangeStart.Location = new System.Drawing.Point(152, 34);
            this.lblRangeStart.Name = "lblRangeStart";
            this.lblRangeStart.Size = new System.Drawing.Size(45, 19);
            this.lblRangeStart.TabIndex = 4;
            this.lblRangeStart.Text = "Start";
            this.lblRangeStart.TextAlign = System.Drawing.ContentAlignment.BottomLeft;
            // 
            // rbtRegex
            // 
            this.rbtRegex.AutoSize = true;
            this.rbtRegex.Font = new System.Drawing.Font("微软雅黑", 9F, ((System.Drawing.FontStyle)((System.Drawing.FontStyle.Bold | System.Drawing.FontStyle.Italic))), System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.rbtRegex.Location = new System.Drawing.Point(7, 145);
            this.rbtRegex.Name = "rbtRegex";
            this.rbtRegex.Size = new System.Drawing.Size(78, 23);
            this.rbtRegex.TabIndex = 3;
            this.rbtRegex.TabStop = true;
            this.rbtRegex.Text = "Match";
            this.rbtRegex.UseVisualStyleBackColor = true;
            // 
            // rbtDepth
            // 
            this.rbtDepth.AutoSize = true;
            this.rbtDepth.Font = new System.Drawing.Font("微软雅黑", 9F, ((System.Drawing.FontStyle)((System.Drawing.FontStyle.Bold | System.Drawing.FontStyle.Italic))), System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.rbtDepth.Location = new System.Drawing.Point(7, 102);
            this.rbtDepth.Name = "rbtDepth";
            this.rbtDepth.Size = new System.Drawing.Size(77, 23);
            this.rbtDepth.TabIndex = 2;
            this.rbtDepth.TabStop = true;
            this.rbtDepth.Text = "Depth";
            this.rbtDepth.UseVisualStyleBackColor = true;
            // 
            // rbtRange
            // 
            this.rbtRange.AutoSize = true;
            this.rbtRange.Font = new System.Drawing.Font("微软雅黑", 9F, ((System.Drawing.FontStyle)((System.Drawing.FontStyle.Bold | System.Drawing.FontStyle.Italic))), System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.rbtRange.Location = new System.Drawing.Point(7, 59);
            this.rbtRange.Name = "rbtRange";
            this.rbtRange.Size = new System.Drawing.Size(78, 23);
            this.rbtRange.TabIndex = 1;
            this.rbtRange.TabStop = true;
            this.rbtRange.Text = "Range";
            this.rbtRange.UseVisualStyleBackColor = true;
            // 
            // rbtAllBytes
            // 
            this.rbtAllBytes.AutoSize = true;
            this.rbtAllBytes.Font = new System.Drawing.Font("微软雅黑", 9F, ((System.Drawing.FontStyle)((System.Drawing.FontStyle.Bold | System.Drawing.FontStyle.Italic))), System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.rbtAllBytes.Location = new System.Drawing.Point(7, 25);
            this.rbtAllBytes.Name = "rbtAllBytes";
            this.rbtAllBytes.Size = new System.Drawing.Size(94, 23);
            this.rbtAllBytes.TabIndex = 0;
            this.rbtAllBytes.TabStop = true;
            this.rbtAllBytes.Text = "All Bytes";
            this.rbtAllBytes.UseVisualStyleBackColor = true;
            // 
            // lblTargetDirectory
            // 
            this.lblTargetDirectory.AutoSize = true;
            this.lblTargetDirectory.Font = new System.Drawing.Font("微软雅黑", 10.8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.lblTargetDirectory.Location = new System.Drawing.Point(26, 100);
            this.lblTargetDirectory.Name = "lblTargetDirectory";
            this.lblTargetDirectory.Size = new System.Drawing.Size(160, 25);
            this.lblTargetDirectory.TabIndex = 1;
            this.lblTargetDirectory.Text = "Target Directory";
            // 
            // lblSourceFile
            // 
            this.lblSourceFile.AutoSize = true;
            this.lblSourceFile.Font = new System.Drawing.Font("微软雅黑", 10.8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.lblSourceFile.Location = new System.Drawing.Point(26, 19);
            this.lblSourceFile.Name = "lblSourceFile";
            this.lblSourceFile.Size = new System.Drawing.Size(112, 25);
            this.lblSourceFile.TabIndex = 0;
            this.lblSourceFile.Text = "Source File";
            // 
            // execute
            // 
            this.execute.Controls.Add(this.tbxCount);
            this.execute.Controls.Add(this.tbxMilliseconds);
            this.execute.Controls.Add(this.tbxFinishFile);
            this.execute.Controls.Add(this.tbxStartFile);
            this.execute.Controls.Add(this.lblCount);
            this.execute.Controls.Add(this.lblMilliseconds);
            this.execute.Controls.Add(this.lblFinishFile);
            this.execute.Controls.Add(this.lblStartFile);
            this.execute.Controls.Add(this.lblExecuteArgs);
            this.execute.Controls.Add(this.tbxExecuteArgs);
            this.execute.Controls.Add(this.tbxExecuteApp);
            this.execute.Controls.Add(this.lblExecuteApp);
            this.execute.Location = new System.Drawing.Point(4, 28);
            this.execute.Name = "execute";
            this.execute.Padding = new System.Windows.Forms.Padding(3);
            this.execute.Size = new System.Drawing.Size(782, 426);
            this.execute.TabIndex = 1;
            this.execute.Text = "Execute";
            // 
            // tbxCount
            // 
            this.tbxCount.Font = new System.Drawing.Font("Microsoft Sans Serif", 34F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.tbxCount.Location = new System.Drawing.Point(369, 292);
            this.tbxCount.Name = "tbxCount";
            this.tbxCount.ReadOnly = true;
            this.tbxCount.RightToLeft = System.Windows.Forms.RightToLeft.Yes;
            this.tbxCount.Size = new System.Drawing.Size(224, 72);
            this.tbxCount.TabIndex = 48;
            this.tbxCount.Text = "0";
            // 
            // tbxMilliseconds
            // 
            this.tbxMilliseconds.Location = new System.Drawing.Point(193, 296);
            this.tbxMilliseconds.Name = "tbxMilliseconds";
            this.tbxMilliseconds.Size = new System.Drawing.Size(119, 25);
            this.tbxMilliseconds.TabIndex = 12;
            this.tbxMilliseconds.Text = "2000";
            // 
            // tbxFinishFile
            // 
            this.tbxFinishFile.Location = new System.Drawing.Point(193, 253);
            this.tbxFinishFile.Name = "tbxFinishFile";
            this.tbxFinishFile.Size = new System.Drawing.Size(119, 25);
            this.tbxFinishFile.TabIndex = 11;
            this.tbxFinishFile.Text = "10";
            // 
            // tbxStartFile
            // 
            this.tbxStartFile.Location = new System.Drawing.Point(193, 218);
            this.tbxStartFile.Name = "tbxStartFile";
            this.tbxStartFile.Size = new System.Drawing.Size(119, 25);
            this.tbxStartFile.TabIndex = 10;
            this.tbxStartFile.Text = "0";
            // 
            // lblCount
            // 
            this.lblCount.AutoSize = true;
            this.lblCount.Font = new System.Drawing.Font("微软雅黑 Light", 22.2F, System.Drawing.FontStyle.Italic, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.lblCount.Location = new System.Drawing.Point(360, 218);
            this.lblCount.Name = "lblCount";
            this.lblCount.Size = new System.Drawing.Size(127, 50);
            this.lblCount.TabIndex = 9;
            this.lblCount.Text = "Count";
            // 
            // lblMilliseconds
            // 
            this.lblMilliseconds.AutoSize = true;
            this.lblMilliseconds.Font = new System.Drawing.Font("微软雅黑", 10.8F, System.Drawing.FontStyle.Italic, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.lblMilliseconds.Location = new System.Drawing.Point(48, 292);
            this.lblMilliseconds.Name = "lblMilliseconds";
            this.lblMilliseconds.Size = new System.Drawing.Size(126, 25);
            this.lblMilliseconds.TabIndex = 8;
            this.lblMilliseconds.Text = "Milliseconds";
            this.lblMilliseconds.TextAlign = System.Drawing.ContentAlignment.BottomLeft;
            // 
            // lblFinishFile
            // 
            this.lblFinishFile.AutoSize = true;
            this.lblFinishFile.Font = new System.Drawing.Font("微软雅黑", 10.8F, System.Drawing.FontStyle.Italic, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.lblFinishFile.Location = new System.Drawing.Point(48, 253);
            this.lblFinishFile.Name = "lblFinishFile";
            this.lblFinishFile.Size = new System.Drawing.Size(102, 25);
            this.lblFinishFile.TabIndex = 7;
            this.lblFinishFile.Text = "Finish File";
            // 
            // lblStartFile
            // 
            this.lblStartFile.AutoSize = true;
            this.lblStartFile.Font = new System.Drawing.Font("微软雅黑", 10.8F, System.Drawing.FontStyle.Italic, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.lblStartFile.Location = new System.Drawing.Point(48, 218);
            this.lblStartFile.Name = "lblStartFile";
            this.lblStartFile.Size = new System.Drawing.Size(92, 25);
            this.lblStartFile.TabIndex = 6;
            this.lblStartFile.Text = "Start File";
            this.lblStartFile.TextAlign = System.Drawing.ContentAlignment.BottomLeft;
            // 
            // lblExecuteArgs
            // 
            this.lblExecuteArgs.AutoSize = true;
            this.lblExecuteArgs.Font = new System.Drawing.Font("微软雅黑", 10.8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.lblExecuteArgs.Location = new System.Drawing.Point(30, 121);
            this.lblExecuteArgs.Name = "lblExecuteArgs";
            this.lblExecuteArgs.Size = new System.Drawing.Size(113, 25);
            this.lblExecuteArgs.TabIndex = 5;
            this.lblExecuteArgs.Text = "Arguments";
            // 
            // tbxExecuteArgs
            // 
            this.tbxExecuteArgs.Location = new System.Drawing.Point(35, 171);
            this.tbxExecuteArgs.Name = "tbxExecuteArgs";
            this.tbxExecuteArgs.Size = new System.Drawing.Size(673, 25);
            this.tbxExecuteArgs.TabIndex = 4;
            // 
            // tbxExecuteApp
            // 
            this.tbxExecuteApp.Location = new System.Drawing.Point(33, 76);
            this.tbxExecuteApp.Name = "tbxExecuteApp";
            this.tbxExecuteApp.Size = new System.Drawing.Size(673, 25);
            this.tbxExecuteApp.TabIndex = 2;
            // 
            // lblExecuteApp
            // 
            this.lblExecuteApp.AutoSize = true;
            this.lblExecuteApp.Font = new System.Drawing.Font("微软雅黑", 10.8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.lblExecuteApp.Location = new System.Drawing.Point(30, 30);
            this.lblExecuteApp.Name = "lblExecuteApp";
            this.lblExecuteApp.Size = new System.Drawing.Size(116, 25);
            this.lblExecuteApp.TabIndex = 0;
            this.lblExecuteApp.Text = "Application";
            // 
            // menuStrip1
            // 
            this.menuStrip1.ImageScalingSize = new System.Drawing.Size(20, 20);
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.mnuFile,
            this.mnuEdit});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(1071, 28);
            this.menuStrip1.TabIndex = 28;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // mnuFile
            // 
            this.mnuFile.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.mnuFileExit});
            this.mnuFile.Name = "mnuFile";
            this.mnuFile.Size = new System.Drawing.Size(46, 24);
            this.mnuFile.Text = "&File";
            // 
            // mnuFileExit
            // 
            this.mnuFileExit.Name = "mnuFileExit";
            this.mnuFileExit.Size = new System.Drawing.Size(110, 26);
            this.mnuFileExit.Text = "Exit";
            // 
            // mnuEdit
            // 
            this.mnuEdit.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.mnuEditCopy});
            this.mnuEdit.Name = "mnuEdit";
            this.mnuEdit.Size = new System.Drawing.Size(49, 24);
            this.mnuEdit.Text = "Edit";
            // 
            // mnuEditCopy
            // 
            this.mnuEditCopy.Name = "mnuEditCopy";
            this.mnuEditCopy.Size = new System.Drawing.Size(122, 26);
            this.mnuEditCopy.Text = "&Copy";
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(0, 0);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(75, 23);
            this.button1.TabIndex = 29;
            this.button1.Text = "button1";
            this.button1.UseVisualStyleBackColor = true;
            // 
            // btnSourceFile
            // 
            this.btnSourceFile.Location = new System.Drawing.Point(804, 179);
            this.btnSourceFile.Name = "btnSourceFile";
            this.btnSourceFile.Size = new System.Drawing.Size(150, 33);
            this.btnSourceFile.TabIndex = 7;
            this.btnSourceFile.Text = "Select";
            this.btnSourceFile.UseVisualStyleBackColor = true;
            this.btnSourceFile.Click += new System.EventHandler(this.btnSourceFile_Click);
            // 
            // button3
            // 
            this.button3.Location = new System.Drawing.Point(804, 547);
            this.button3.Name = "button3";
            this.button3.Size = new System.Drawing.Size(156, 44);
            this.button3.TabIndex = 30;
            this.button3.Text = "button3";
            this.button3.UseVisualStyleBackColor = true;
            // 
            // btnTargetDirectory
            // 
            this.btnTargetDirectory.Location = new System.Drawing.Point(808, 254);
            this.btnTargetDirectory.Name = "btnTargetDirectory";
            this.btnTargetDirectory.Size = new System.Drawing.Size(141, 36);
            this.btnTargetDirectory.TabIndex = 31;
            this.btnTargetDirectory.Text = "Select";
            this.btnTargetDirectory.UseVisualStyleBackColor = true;
            this.btnTargetDirectory.Click += new System.EventHandler(this.btnTargetDirectory_Click);
            // 
            // btnCreateFiles
            // 
            this.btnCreateFiles.Location = new System.Drawing.Point(807, 307);
            this.btnCreateFiles.Name = "btnCreateFiles";
            this.btnCreateFiles.Size = new System.Drawing.Size(147, 36);
            this.btnCreateFiles.TabIndex = 32;
            this.btnCreateFiles.Text = "Create";
            this.btnCreateFiles.UseVisualStyleBackColor = true;
            // 
            // ofdSourceFile
            // 
            this.ofdSourceFile.FileName = "openFileDialog1";
            this.ofdSourceFile.Filter = "All files (*.*)|*.*|All files (*.*)|*.*";
            this.ofdSourceFile.FilterIndex = 2;
            this.ofdSourceFile.InitialDirectory = "c:\\";
            this.ofdSourceFile.RestoreDirectory = true;
            this.ofdSourceFile.Title = "Select Source File";
            // 
            // frmFileFuzz
            // 
            this.AccessibleRole = System.Windows.Forms.AccessibleRole.IpAddress;
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1071, 739);
            this.Controls.Add(this.btnCreateFiles);
            this.Controls.Add(this.btnTargetDirectory);
            this.Controls.Add(this.button3);
            this.Controls.Add(this.btnSourceFile);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.tclMain);
            this.Controls.Add(this.checkBox2);
            this.Controls.Add(this.cbxStripFileExt);
            this.Controls.Add(this.cbxFileType);
            this.Controls.Add(this.lblFileType);
            this.Controls.Add(this.menuStrip1);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MainMenuStrip = this.menuStrip1;
            this.Name = "frmFileFuzz";
            this.Text = "FileFuzz";
            this.Load += new System.EventHandler(this.frmFileFuzz_Load);
            this.tclMain.ResumeLayout(false);
            this.create.ResumeLayout(false);
            this.create.PerformLayout();
            this.gbxTarget.ResumeLayout(false);
            this.gbxTarget.PerformLayout();
            this.gbxScope.ResumeLayout(false);
            this.gbxScope.PerformLayout();
            this.execute.ResumeLayout(false);
            this.execute.PerformLayout();
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label lblFileType;
        private System.Windows.Forms.ComboBox cbxFileType;
        public System.Windows.Forms.CheckBox cbxStripFileExt;
        private System.Windows.Forms.CheckBox checkBox2;
        private System.Windows.Forms.TabControl tclMain;
        private System.Windows.Forms.TabPage create;
        private System.Windows.Forms.TabPage execute;
        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.Label lblTargetDirectory;
        private System.Windows.Forms.Label lblSourceFile;
        private System.Windows.Forms.ToolStripMenuItem mnuFile;
        private System.Windows.Forms.ToolStripMenuItem mnuEdit;
        private System.Windows.Forms.TextBox textBox2;
        private System.Windows.Forms.TextBox textBox1;
        private System.Windows.Forms.Label lblExecuteArgs;
        private System.Windows.Forms.TextBox tbxExecuteArgs;
        private System.Windows.Forms.TextBox tbxExecuteApp;
        private System.Windows.Forms.Label lblExecuteApp;
        private System.Windows.Forms.GroupBox gbxTarget;
        private System.Windows.Forms.GroupBox gbxScope;
        private System.Windows.Forms.ToolStripMenuItem mnuFileExit;
        private System.Windows.Forms.ToolStripMenuItem mnuEditCopy;
        public System.Windows.Forms.Label lbltbxTargetBytes;
        private System.Windows.Forms.TextBox tbxTargetBytesNumber;
        private System.Windows.Forms.TextBox tbxTargetByte;
        private System.Windows.Forms.TextBox tbxTargetByteFinish;
        public System.Windows.Forms.Label lblTargetBytesMultiple;
        private System.Windows.Forms.TextBox textBox6;
        private System.Windows.Forms.TextBox textBox5;
        private System.Windows.Forms.TextBox textBox4;
        private System.Windows.Forms.TextBox textBox3;
        private System.Windows.Forms.Label lblRegexReplace;
        private System.Windows.Forms.Label lblRegexFind;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label lblRangeStart;
        private System.Windows.Forms.RadioButton rbtRegex;
        private System.Windows.Forms.RadioButton rbtDepth;
        private System.Windows.Forms.RadioButton rbtRange;
        private System.Windows.Forms.RadioButton rbtAllBytes;
        private System.Windows.Forms.TextBox tbxMilliseconds;
        private System.Windows.Forms.TextBox tbxFinishFile;
        private System.Windows.Forms.TextBox tbxStartFile;
        private System.Windows.Forms.Label lblCount;
        private System.Windows.Forms.Label lblMilliseconds;
        private System.Windows.Forms.Label lblFinishFile;
        private System.Windows.Forms.Label lblStartFile;
        private System.Windows.Forms.TextBox tbxCount;
        private System.Windows.Forms.TextBox tbxSourceFile1;
        private System.Windows.Forms.TextBox tbxTargetDirectory;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.Button btnSourceFile;
        private System.Windows.Forms.Button button3;
        private System.Windows.Forms.Button btnTargetDirectory;
        private System.Windows.Forms.Button btnCreateFiles;
        private System.Windows.Forms.OpenFileDialog ofdSourceFile;
        private System.Windows.Forms.FolderBrowserDialog fbdTargetDirectory;
    }
}

