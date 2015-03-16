#!/bin/bash

cat -n source/tree.h | grep define | grep TREE > treemacros
less treemacros
