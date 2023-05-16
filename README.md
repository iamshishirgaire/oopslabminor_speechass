# oopslabminor_speechass

sudo yum update
sudo yum groupinstall "Development tools"
sudo yum install alsa-lib openssl wget

//Choose a directory to which the Speech SDK files should be extracted, and set the SPEECHSDK_ROOT environment variable to point to that directory. This variable makes it easy to refer to the directory in future commands.

//For example, if you want to use the directory speechsdk in your home directory, use a command like the following:

//IN THE .BASHRC FILE ADD THESE TWO LINES AT THE BOTTOM.

export SPEECHSDK_ROOT="$HOME/speechsdk"

After that Create the directory if it doesn't exist yet:

mkdir -p "$SPEECHSDK_ROOT"

cd speechsdk

//Download and extract the .tar.gz archive that contains the Speech SDK binaries:

wget -O SpeechSDK-Linux.tar.gz https://aka.ms/csspeech/linuxbinary tar --strip 1 -xzf SpeechSDK-Linux.tar.gz -C "$SPEECHSDK_ROOT"

//Validate the contents of the top-level directory of the extracted package:

ls -l "$SPEECHSDK_ROOT"

//To run the sample, you'll need to configure the loader's library path to point to the Speech SDK library.

//On an x64 machine, run:

export LD_LIBRARY_PATH="$LD_LIBRARY_PATH:$SPEECHSDK_ROOT/lib/x64"

//On an x86 machine, run:

export LD_LIBRARY_PATH="$LD_LIBRARY_PATH:$SPEECHSDK_ROOT/lib/x86"

//On an ARM64 machine, run:

export LD_LIBRARY_PATH="$LD_LIBRARY_PATH:$SPEECHSDK_ROOT/lib/arm64"
Run the application:

make

./build/recogspeech
