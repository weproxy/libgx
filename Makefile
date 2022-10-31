#
# weproxy@foxmail.com 2022/10/31
#

GOOS ?= $(shell go env GOOS)
GOARCH ?= $(shell go env GOARCH)
GOARM ?= $(shell go env GOARM)

env ?= debug
ENV ?= ${env}

ifeq (${GOOS},darwin)
	GOOS=macosx
endif

ifeq (${GOARCH},amd64)
	GOARCH=x86_64
else ifeq (${GOARCH},386)
	GOARCH=i386
endif

.PHONY: pre all build run clean deploy

all: build

config:
	xmake config -m ${ENV} -p ${GOOS} -a ${GOARCH}

build: config
	xmake build

run: build
	xmake run

clean: config
	xmake clean
