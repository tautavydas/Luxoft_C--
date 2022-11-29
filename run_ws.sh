#! /bin/bash
ARCHITECTURE=${1:-arm64}
docker run --name c003ws --rm -v `pwd`:/home/developer/ws -it alexkutsan/c003:$ARCHITECTURE 