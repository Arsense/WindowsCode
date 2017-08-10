using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MyFuzzTool
{
    class Write
    {

        private int finishByte;
        private byte bytesToWrite;
        private string targetDirectory;
        private int repeatBytes;
        private string fileExtension;
        private int finishFile;
        private byte[] sourceArray;
        private int startByte = 0;
        private int startFile = 0;
        //All bytes 读取所有字节
        public Write(byte[] sourceArrayInput, int finishByteInput, byte bytesToWriteInput, string targetDirectoryInput, string fileExtensionInput, int repeatBytesInput)
        {

            sourceArray = sourceArrayInput;
            finishByte = finishByteInput;
            bytesToWrite = bytesToWriteInput;
            targetDirectory = targetDirectoryInput;
            fileExtension = fileExtensionInput;
            repeatBytes = repeatBytesInput;
            finishFile = finishByte;

        }
        //Range of bytes  有范围的读取
        public Write(byte[] sourceArrayInput, int startByteInput, int finishByteInput, byte bytesToWriteInput, string targetDirectoryInput, string fileExtensionInput, int repeatBytesInput)
        {
            sourceArray = sourceArrayInput;
            startByte = startByteInput;
            finishByte = finishByteInput;
            bytesToWrite = bytesToWriteInput;
            targetDirectory = targetDirectoryInput;
            fileExtension = fileExtensionInput;
            repeatBytes = repeatBytesInput;
            startFile = startByte;
            finishFile = finishByte;
        }





    }


  

}
