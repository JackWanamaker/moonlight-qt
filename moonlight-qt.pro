TEMPLATE = subdirs
SUBDIRS = \
    moonlight-common-c \
    qmdnsengine \
    app

# Build the dependencies in parallel before the final app
app.depends = qmdnsengine moonlight-common-c

# Support debug and release builds from command line for CI
CONFIG += debug_and_release

# Run our compile tests
load(configure)
qtCompileTest(SLVideo)
