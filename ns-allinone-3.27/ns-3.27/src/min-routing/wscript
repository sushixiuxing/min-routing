# -*- Mode: python; py-indent-offset: 4; indent-tabs-mode: nil; coding: utf-8; -*-

# def options(opt):
#     pass

# def configure(conf):
#     conf.check_nonfatal(header_name='stdint.h', define_name='HAVE_STDINT_H')

def build(bld):
    module = bld.create_ns3_module('min-routing', ['internet'])
    module.source = [
        'model/min-routing-protocol.cc',
        'helper/min-routing-helper.cc',
        'model/min-routing-header.cc',
        'model/min-routing-state.cc',
        ]


    module_test = bld.create_ns3_module_test_library('min-routing')
    module_test.source = [
        'test/min-routing-test-suite.cc',
        ]


    headers = bld(features='ns3header')
    headers.module = 'min-routing'
    headers.source = [
        'model/min-routing-protocol.h',
        'helper/min-routing-helper.h',
        'model/min-routing-repositories.h',
        'model/min-routing-state.h',
        'model/min-routing-header.h',
        ]

    if bld.env.ENABLE_EXAMPLES:
        bld.recurse('examples')

    # bld.ns3_python_bindings()

