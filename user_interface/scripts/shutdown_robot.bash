#!/bin/bash

rosnode kill -a
kill $(ps --no-headers -C roscore -o pid)
