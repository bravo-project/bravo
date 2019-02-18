# Bravo - The Decentralized Consumer Review Blockchain That Pays Its Community

Welcome to the official repository for Bravo, the review blockchain that pays its community!

Bravo is a blockchain-based consumer review platform with its own token called BRAVO. Bravo runs a modified version of Steem's "Proof-of-Brain" algorithm. An algorithm that distributes token-based rewards to encourage reviewers and contributors to create and curate unique content.

Bravo is the first review blockchain to harness Steemit’s "Proof of Brain" social consensus algorithm for token allocation.

Bravo aims to solve 5 critical flaws in current Web 2.0 review platforms:

*	Centralization
*	Manipulation
*	Censorship
* 	Transparency
*	Bias

By providing an immutable, trustless, and decentralized blockchain based review platform, we can eliminate centralization and censorship, and vastly improve against bias and manipulation via communal efforts and rewards.

## Downloads

*	Android - https://play.google.com/store/apps/details?id=com.bravocoin.app
*	iOS - https://itunes.apple.com/us/app/bravo-food-hotels-services/id1441407366?mt=8

## Technical Details

*	Currency symbol BRAVO
*	Delegated Proof-of-Stake Consensus (DPOS)
*	Forked at Steemit HF 19

## Installation

Getting started with Bravo is easy. You can either choose to use docker-images, build with docker manually or build from source directly. All steps have been documented and while many different OS are supported, the easiest one is Ubuntu 16.04.

## Quickstart

Just want to get up and running quickly? We have pre-built Docker images for your convenience. More details are in our Quickstart Guide.

## Building

We strongly recommend using one of our pre-built Docker images or using Docker to build Bravo. Both of these processes are described in the Quickstart Guide.

But if you would still like to build from source, we also have build instructions for Linux (Ubuntu LTS) and macOS. Dockerized P2P Node

To run a p2p node (ca. 2GB of memory is required at the moment):

```
	docker run \
    		-d -p 2001:2001 -p 8090:8090 --name bravod-default \
    		bravocoin/bravocoin

	docker logs -f bravod-default  # follow along
```

## Dockerized Full Node

To run a node with all the data (e.g. for supporting a content website) ca. 14GB of memory, and growing, is required:

```
	docker run \
		--env USE_WAY_TOO_MUCH_RAM=1 --env USE_FULL_WEB_NODE=1 \
		-d -p 2001:2001 -p 8090:8090 --name bravod-full \
	bravocoin/bravocoin

 	docker logs -f bravod-full
```

## Building from Source - Ubuntu 16.04 LTS

## Dependency Installation

```
sudo apt-get install -y \
	autoconf \ 
	automake \ 
	cmake \ 
	g++ \ 
	git \ 
	libssl-dev \ 
	libtool \ 
	make \ 
	pkg-config \ 
	python3 \ 
	python3-jinja2 \
	libboost-chrono-dev \ 
	libboost-context-dev \ 
	libboost-coroutine-dev \ 
	libboost-date-time-dev \ 
	libboost-filesystem-dev \ 
	libboost-iostreams-dev \ 
	libboost-locale-dev \ 
	libboost-program-options-dev \ 
	libboost-serialization-dev \ 
	libboost-signals-dev \ 
	libboost-system-dev \ 
	libboost-test-dev \ 
	libboost-thread-dev
```

## Optional packages

```	
	sudo apt-get install -y \ 
	doxygen \ 
	libncurses5-dev \ 
	libreadline-dev \ 
	perl
```

## Git Submodule update

```
	git submodule update --init --recursive
```

## Build Options

```
cmake -DCMAKE_BUILD_TYPE=Release -DENABLE_CONTENT_PATCHING=OFF -DLOW_MEMORY_NODE=ON -DBUILD_BRAVO_TESTNET=OFF
make OR make -j$(nproc) bravod OR make -j$(nproc) cli_wallet
```

## CLI Wallet

We provide a basic cli wallet for interfacing with bravod. The wallet is self-documented via command line help. The node you connect to via the cli wallet needs to be running the account_by_key_api, condenser_api, and needs to be configured to accept WebSocket connections via webserver-ws-endpoint.

## Testing

See doc/testing.md for test build targets and info on how to use lcov to check code test coverage.

## Configuration

## Config File
Run bravod once to generate a data directory and config file. The default location is witness_node_data_dir. Kill bravod. It won't do anything without seed nodes. If you want to modify the config to your liking, we have two example configs used in the docker images. ( consensus node, full node ) All options will be present in the default config file and there may be more options needing to be changed from the docker configs (some of the options actually used in images are configured via command line).

## Seed Nodes

A list of some seed nodes to get you started can be found in doc/seednodes.txt.
This same file is baked into the docker images and can be overridden by setting BRAVOD_SEED_NODES in the container environment at docker run time to a whitespace delimited list of seed nodes (with port).

## Environment variables

There are quite a few environment variables that can be set to run bravod in different ways:
*	USE_WAY_TOO_MUCH_RAM - if set to true, bravod starts a 'full node'
*	USE_FULL_WEB_NODE - if set to true, a default config file will be used that enables a full set of API's and associated plugins.
*	USE_NGINX_FRONTEND - if set to true, this will enable an NGINX reverse proxy in front of bravod that proxies WebSocket requests to bravod. This will also enable a custom healthcheck at the path '/health' that lists how many seconds away from current blockchain time your node is. It will return a '200' if it's less than 60 seconds away from being synced.
*	USE_MULTICORE_READONLY - if set to true, this will enable bravod in multiple reader mode to take advantage of multiple cores (if available). Read requests are handled by the read-only nodes and write requests are forwarded back to the single 'writer' node automatically. NGINX load balances all requests to the reader nodes, 4 per available core. This setting is still considered experimental and may have trouble with some API calls until further development is completed.
*	HOME - set this to the path where you want bravod to store it's data files (block log, shared memory, config file, etc). By default /var/lib/bravod is used and exists inside the docker container. If you want to use a different mount point (like a ramdisk, or a different drive) then you may want to set this variable to map the volume to your docker container.

## PaaS mode

Bravod now supports a PaaS mode (platform as a service) that currently works with Amazon's Elastic Beanstalk service. It can be launched using the following environment variables:

*	USE_PAAS - if set to true, bravod will launch in a format that works with AWS EB. Containers will exit upon failure so that they can be relaunched automatically by ECS. This mode assumes USE_WAY_TOO_MUCH_RAM and USE_FULL_WEB_NODE, they do not need to be also set.
*	S3_BUCKET - set this to the name of the S3 bucket where you will store shared memory files for bravod in Amazon S3. They will be stored compressed in bz2 format with the file name blockchain-$VERSION-latest.tar.bz2, where $VERSION is the release number followed by the git short commit hash stored in each docker image at /etc/bravodversion.
*	SYNC_TO_S3 - if set to true, the node will function to only generate shared memory files and upload them to the specified S3 bucket. This makes fast deployments and autoscaling for bravod possible.

## System Requirements

For a full web node, we recommend 40GB of disk space available to account for future chain data. It's highly recommended to run bravod on a fast disk such as an SSD or by placing the shared memory files in a ramdisk and using the --shared-file-dir=/path command line option to specify where. At least 16GB of memory is required for a full web node. Seed nodes (p2p mode) can run with as little as 4GB of memory with a 24 GB state file. Any CPU with decent single core performance should be sufficient. Bravod is constantly growing.

On Linux use the following Virtual Memory configuration for the initial sync and subsequent replays. It is not needed for normal operation.

```
	echo    75 | sudo tee /proc/sys/vm/dirty_background_ratio
	echo  1000 | sudo tee /proc/sys/vm/dirty_expire_centisecs
	echo    80 | sudo tee /proc/sys/vm/dirty_ratio
	echo 30000 | sudo tee /proc/sys/vm/dirty_writeback_centisecs
```

## No Support & No Warranty

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
