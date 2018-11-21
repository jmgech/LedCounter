<?
	
	class Socials {
		public $instagram;
		public $facebook;
		public $twitter;
		public $youtube;
		public $cocktail;
		
		
		public function getTwitter($profileId){
			
			$followers = "";
			
			if(isset($profileId)){
				$path = "http://cdn.syndication.twimg.com/widgets/followbutton/info.json?screen_names=" . $profileId . "&" . mt_rand();
				
				$response = file_get_contents($path);
				
				if($response!=false){
					$data = json_decode($response, true);
					if ($data !== null) {
						$this->twitter = (int)$data[0]["followers_count"];
					}
					
				
					
				}
				
			}
			
		}
		
		
		public function getYoutube($channelId, $apiKey){
			
			if(isset($channelId)){
				
				$path = 'https://www.googleapis.com/youtube/v3/channels?part=statistics&id='.$channelId.'&fields=items/statistics/subscriberCount&key='.$apiKey;

				$response = file_get_contents($path);
				
				if($response!=false){
					$data = json_decode($response, true);
					
				}
				
				
				$this->youtube = (int)$data['items'][0]['statistics']['subscriberCount']; 
				
			}
			
			
		}

		public function getInstagram($userid){
			
			
			if(isset($userid)){
				
				$response = $this->getPublicInfo($userid);
				
				if($response!=false){
					$this->instagram = (int)$response['user']['edge_followed_by']['count'];
					
				}
				
			}
			
			
		}
		
		public function getCocktail($userid){
			/* I should really think about setting up a cocktail social feed :D */
			$this->cocktail = (int)rand(1, 9999);			
		}
		
		
		public function getFeed(){ }
		
		
		function getPublicInfo($username) {
		    $url     = sprintf("https://www.instagram.com/$username");
		    $content = file_get_contents($url);
		    $content = explode("window._sharedData = ", $content)[1];
		    $content = explode(";</script>", $content)[0];
		    $data    = json_decode($content, true);
		    		    
		    return $data['entry_data']['ProfilePage'][0]['graphql'];
		}
		
		
				
		
	}
	
	$socials = new Socials();
	$socials->getTwitter(""); 		// Twitter account name
	$socials->getYoutube("", ""); 	// Youtube Channel ID and API Key
	$socials->getInstagram(""); 	// Instagram account name
	$socials->getCocktail(""); 		// Not a real social network. I should create it.
	
	echo(json_encode(get_object_vars($socials)));
	
	
	
	
	
	
	