<?php

if($items){
	
	foreach($items as $item){
		
		$genid = "taxonomy:" . $item['#options']['entity']->tid;
		$lid_array = location_load_locations($genid,"genid");
		
		// as specified in location.module for the function location_theme();
		$tpl_vars = array('location' => $lid_array[0], 'hide' => array() );

		print l($item['#title'],$item['#href']);
		print "teaser-template";
	}
	
}

