{
    'targets': [
        {
            'target_name': 'awslambda',
            'sources': [
                'src/awslambda.cc'
            ],
            'include_dirs': [
                '$(BP_LIBFARM)/include'
            ],
            'link_settings': {
                'ldflags' : [
                    '-L$(BP_LIBFARM)/lib',
                    '$(BP_LINKLIBS)'
                ]
            }
        }
    ]
}
