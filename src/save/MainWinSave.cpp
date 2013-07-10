#include "../MainWin.hpp"

void MainWin::save()
{
	
	QString javascriptQuery = R"delimiter($.ajax({
		type: "POST",//Envoi des donnÃ©es avec la mÃ©thode POST
		url: "scripts/save.php",//Ã  la page sauvegarde.php
		data: {
			code : ((code === undefined || code == null || code.length == "") ? 0 : code),
			swordName : sword.name,
			swordSpecialSword : getPhpStuff(sword.specialSword),
			swordSpecialPower : sword.specialPower,
			candiesNbrOwned : candies.nbrOwned,
			candiesNbrThrown : candies.nbrThrown,
			candiesNbrEaten : candies.nbrEaten,
			candiesNbrTotal : candies.nbrTotal,
			candiesCandiesPerSecond : candies.candiesPerSecond,
			candiesConverterActivated : getPhpStuff(candiesConverter.activated),
			cauldronBookPage : cauldron.bookPage,
			cauldronCandies : cauldron.candiesInTheCauldron,
			cauldronLollipops : cauldron.lollipopsInTheCauldron,
			chocolateBarsNbrOwned : chocolateBars.nbrOwned,
			farmLollipopsPlanted : farm.lollipopsPlanted,
			farmCurrentFlagIndex : farm.currentFlagIndex,
			farmPlantingButtonsStep : farm.plantingButtonsStep,
			forgeStep : forge.step,
			shopLollipopsButtonsShown : getPhpStuff(shop.buy10LollipopsButtonShown),
			shopShown : getPhpStuff(shop.shown),
			shopTicklingStep : shop.ticklingStep,
			shopClickingOnLollipopStep : shop.clickingOnLollipopStep,
			hutStep : hut.step,
			hutSpeech : hut.speech,
			inventoryMagicianHatLetter : inventory.magicianHatLetter,
			lollipopsNbrOwned : lollipops.nbrOwned,
			lollipopsNbrInStock : lollipops.nbrInStock,
			lollipopsNbrBought : lollipops.nbrBought,
			mainNbrOfSecondsSinceLastMinInterval : main.nbrOfSecondsSinceLastMinInterval,
			mainNbrOfSecondsSinceLastHourInterval : main.nbrOfSecondsSinceLastHourInterval,
			mainNbrOfSecondsSinceLastDayInterval : main.nbrOfSecondsSinceLastDayInterval,
			mountGoblinBasicChestProbability : mountGoblin.basicChestProbability,
			peacefulForestBasicChestProbability : peacefulForest.basicChestProbability,
			peacefulForestPoniesEncountered : peacefulForest.poniesEncountered,
			objectsHaveObjectKey : getPhpStuff(objects.list.key.have),
			objectsHaveObjectHutMap : getPhpStuff(objects.list.hutMap.have),
			objectsHaveObjectWellMap : getPhpStuff(objects.list.wellMap.have),
			objectsHaveObjectSwampMap : getPhpStuff(objects.list.swampMap.have),
			objectsHaveObjectBoots : getPhpStuff(objects.list.boots.have),
			objectsHaveObjectMagicianHat : getPhpStuff(objects.list.magicianHat.have),
			objectsHaveObjectPinkRing : getPhpStuff(objects.list.pinkRing.have),
			objectsHaveObjectForgeMap : getPhpStuff(objects.list.forgeMap.have),
			objectsHaveObjectCandiesConverter : getPhpStuff(objects.list.candiesConverter.have),
			objectsHaveObjectPlateArmour : getPhpStuff(objects.list.plateArmour.have),
			objectsHaveObjectCauldron : getPhpStuff(objects.list.cauldron.have),
			objectsHaveObjectMagicalHorn : getPhpStuff(objects.list.magicalHorn.have),
			objectsHaveObjectHornOfPlenty : getPhpStuff(objects.list.hornOfPlenty.have),
			objectsHaveObjectOldAmulet : getPhpStuff(objects.list.oldAmulet.have),
			potionsShownHealth : getPhpStuff(potions.list.health.shown),
			potionsShownEscape : getPhpStuff(potions.list.escape.shown),
			potionsShownBerserk : getPhpStuff(potions.list.berserk.shown),
			potionsShownFireScroll : getPhpStuff(potions.list.fireScroll.shown),
			potionsShownAcidRainScroll : getPhpStuff(potions.list.acidRainScroll.shown),
			potionsShownTeleportScroll : getPhpStuff(potions.list.teleportScroll.shown),
			potionsShownEarthquakeScroll : getPhpStuff(potions.list.earthquakeScroll.shown),
			potionsShownImpInvocationScroll : getPhpStuff(potions.list.impInvocationScroll.shown),
			potionsShownMajorHealth : getPhpStuff(potions.list.majorHealth.shown),
			potionsShownInvulnerability : getPhpStuff(potions.list.invulnerability.shown),
			potionsShownTurtle : getPhpStuff(potions.list.turtle.shown),
			potionsShownJelly : getPhpStuff(potions.list.jelly.shown),
			potionsShownSeed : getPhpStuff(potions.list.seed.shown),
			potionsShownCloning : getPhpStuff(potions.list.cloning.shown),
			potionsShownSuperman : getPhpStuff(potions.list.superman.shown),
			potionsShownGmooh : getPhpStuff(potions.list.gmooh.shown),
			potionsNbrOwnedHealth : potions.list.health.nbrOwned,
			potionsNbrOwnedEscape : potions.list.escape.nbrOwned,
			potionsNbrOwnedBerserk : potions.list.berserk.nbrOwned,
			potionsNbrOwnedFireScroll : potions.list.fireScroll.nbrOwned,
			potionsNbrOwnedAcidRainScroll : potions.list.acidRainScroll.nbrOwned,
			potionsNbrOwnedTeleportScroll : potions.list.teleportScroll.nbrOwned,
			potionsNbrOwnedEarthquakeScroll : potions.list.earthquakeScroll.nbrOwned,
			potionsNbrOwnedImpInvocationScroll : potions.list.impInvocationScroll.nbrOwned,
			potionsNbrOwnedMajorHealth : potions.list.majorHealth.nbrOwned,
			potionsNbrOwnedInvulnerability : potions.list.invulnerability.nbrOwned,
			potionsNbrOwnedTurtle : potions.list.turtle.nbrOwned,
			potionsNbrOwnedJelly : potions.list.jelly.nbrOwned,
			potionsNbrOwnedSeed : potions.list.seed.nbrOwned,
			potionsNbrOwnedCloning : potions.list.cloning.nbrOwned,
			potionsNbrOwnedSuperman : potions.list.superman.nbrOwned,
			potionsNbrOwnedGmooh : potions.list.gmooh.nbrOwned,
			questMaxLandOrder : quest.maxLandOrder,
			questTiredTime : quest.tiredTime,
			spellsFasterCandiesFibo1 : spells.fasterCandiesFiboPrev,
			spellsFasterCandiesFibo2 : spells.fasterCandiesFiboCurr,
			swampStep : swamp.step,
			tabsAnimation : tabs.animation,
			wishingWellSpeech : wishingWell.speech,
			wishingWellStep : wishingWell.step,
			yourselfCanSurpass : getPhpStuff(yourself.canSurpass),
			developperComputerWon : getPhpStuff(developperComputer.won)
		},
	   success: function(msg){//Une fois la requÃªte terminÃ©e
			if(msg=="Erreur"){ //Si la sauvegarde Ã  Ã©chouÃ©e
			
				// Alors on affiche un message
                                alert("There was a problem while saving. Please try again later :/");   
				$("span#save").html("");
				
			}else{ // si la sauvegarde Ã  fonctionnÃ©e
			
				// on affiche le lien de chargement
                                if(msg.substring(0,5) != "<br /"){ 
				code = msg.substring(0,5);
								
                                $("span#save").html(" You can load your save later <a href=\"http://candies.aniwey.net/index.php?pass=" + code + "\">here</a>.");
						        }
                                else{
                                    alert("There was a problem while saving. Please try again later :/");    
                                }
                        }
	   }
	});)delimiter";
				
	for(int i = 0 ; i < _tab->count() ; i ++)
	{
		_tab->widget(i)->findChild<QWebView *>()->page()->mainFrame()->evaluateJavaScript(javascriptQuery);
	}
}