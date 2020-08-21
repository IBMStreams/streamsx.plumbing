---
title: "Toolkit Development overview"
permalink: /docs/developer/overview/
excerpt: "Contributing to this toolkits development."
last_modified_at: 2020-08-21T11:37:48-04:00
redirect_from:
   - /theme-setup/
sidebar:
   nav: "developerdocs"
---
{% include toc %}
{% include editme %}



## Downloading the Streams Plumbing toolkit

Download the full toolkit requires git. Enter a directory of your choice and execute :

`cd yourDirectory`

`git clone https://github.com/IBMStreams/streamsx.plumbing.git`

## Build the toolkit using ant

* Go to the toolkit's main directory that holds the `build.xml` file, for example: `cd /yourDirectory/streamsx.plumbing`
* Run `ant`
* To check out more targets of the build script run: `ant -p`


## Clean the toolkit

To delete generated files, execute:

`ant clean`

