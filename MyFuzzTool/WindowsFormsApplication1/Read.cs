using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using System.Windows.Forms;

namespace MyFuzzTool
{
    public class Read
    {
        private StreamReader StreamReadSourceFile;
        private BinaryReader BinaryReadSourceFile;
        private byte[] SourceArray;
        private String SourceString;
        private int sourceCount;
        private string sourceFile;
        public string sourceString;
        //初始化构造函数
        public Read(String fileName) {
            sourceFile = fileName;
            
        }


        public bool readAscii()
        {
            try
            {
                //从文件流一字节读取
                StreamReadSourceFile = new StreamReader(File.Open(sourceFile, FileMode.Open));
            }
            catch (System.IO.FileNotFoundException ex)
            {
                //没有找到文件
                MessageBox.Show(ex.Message, "Error - Source File Not Found");
                return false;
            }
            catch (System.IO.DirectoryNotFoundException ex)
            {
                //没有找到目录
                MessageBox.Show(ex.Message, "Error - Source Directory Not Found");
                return false;
            }
            catch (System.IO.IOException ex)
            {
                //没有文件访问权限
                MessageBox.Show(ex.Message, "Error - File cannot be accessed");
                return false;
            }
            catch (System.UnauthorizedAccessException ex)
            {
                //没有读取权限
                MessageBox.Show(ex.Message, "Error - Access to the file is denied");
                return false;
            }
            while (StreamReadSourceFile.Peek() != -1) {
                sourceString = Convert.ToChar(StreamReadSourceFile.Read()).ToString();
            }
            StreamReadSourceFile.Close();



            return true;
        }

        //二进制读取
        public bool readBinary() {

            try
            {
                BinaryReadSourceFile = new BinaryReader(File.Open(sourceFile, FileMode.Open));
            }
            catch (System.IO.FileNotFoundException ex)
            {
                MessageBox.Show(ex.Message, "Error - Source File Not Found");
                return false;
            }
            catch (System.IO.DirectoryNotFoundException ex)
            {
                MessageBox.Show(ex.Message, "Error - Source Directory Not Found");
                return false;
            }
            catch (System.IO.IOException ex)
            {
                MessageBox.Show(ex.Message, "Error - File cannot be accessed");
                return false;
            }
            catch (System.UnauthorizedAccessException ex)
            {
                MessageBox.Show(ex.Message, "Error - Access to the file is denied");
                return false;
            }
            //转换成字节流

            SourceArray = new byte[BinaryReadSourceFile.BaseStream.Length];

            try
            {
                while (BinaryReadSourceFile.PeekChar() != -1)
                {
                    SourceArray[sourceCount] = BinaryReadSourceFile.ReadByte();
                    sourceCount++;
                }
                BinaryReadSourceFile.Close();
            }
            catch (System.ArgumentException ex)
            {
                MessageBox.Show(@"Count: " + sourceCount.ToString() + " " + ex.Message, "Error");
                return true;
            }
            return true;
        }

    }
}
