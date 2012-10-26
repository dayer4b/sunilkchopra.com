<?php

if($items){
	
	foreach($items as $item){
		
		print "<div class='field-image'>" 
		. "<a href='" . image_style_url("large",$item["#item"]["uri"]) . "'>" 
		. "<img src='" . image_style_url("thumbnail",$item["#item"]["uri"]) . "' />" 
		. "</a>" 
		. "</div>";
		
	}
	
}

