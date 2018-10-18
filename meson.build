project('thingyjp-connector-mqtt', 'c')

mosquittomainloop = subproject('mosquittomainloop')

src = ['thingyjp_connector_mqtt.c']
deps = [ dependency('glib-2.0'), 
         mosquittomainloop.get_variable('mosquittomainloop_dep')]

executable('thingyjp_connector_mqtt', src, 
           dependencies : deps, 
           install : true,
           install_dir : 'sbin')