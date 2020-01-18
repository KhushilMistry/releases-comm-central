# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.

from __future__ import absolute_import, print_function, unicode_literals

import os
import logging
from importlib import import_module

from taskgraph import GECKO

logger = logging.getLogger(__name__)

COMM = os.path.join(GECKO, 'comm')


def register(graph_config):
    """
    Import all modules that are siblings of this one, triggering decorators in
    the process.
    """
    logger.info("{} path registered".format(__name__))
    _import_modules([])


def _import_modules(modules):
    for module in modules:
        import_module(".{}".format(module), package=__name__)
