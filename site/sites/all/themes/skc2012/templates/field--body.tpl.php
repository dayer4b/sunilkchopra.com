<?php

if($items){
	
	foreach($items as $item){
		print "<div class='body'>" . $item['#markup'] . "</div>";
	}
	
}

