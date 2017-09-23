echo "If I show a permission denied error after this, try running me with sudo...\n"

# Build the docker image, then run the build script in the docker image.
docker build . -t skyshark-builder && \
docker run -v "`pwd`":/docker -it skyshark-builder \
	/bin/bash -c 'cd /docker && ./build.sh '$@

# Fix permissions, if needed
if [ -n "$SUDO_USER" ]; then
	chown -R $SUDO_USER .
fi
