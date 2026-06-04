#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>

using namespace geode::prelude;

class NemoMenu : public CCLayer {
public:
    static NemoMenu* create() {
        auto ret = new NemoMenu();
        if (ret && ret->init()) {
            ret->autorelease();
            return ret;
        }

        delete ret;
        return nullptr;
    }

    bool init() override {
        if (!CCLayer::init())
            return false;

        auto winSize = CCDirector::sharedDirector()->getWinSize();

        auto bg = CCLayerColor::create(
            ccc4(0, 0, 0, 180),
            250,
            180
        );

        bg->setPosition(
            winSize.width / 2 - 125,
            winSize.height / 2 - 90
        );

        this->addChild(bg);

        auto title = CCLabelBMFont::create(
            "Nemo Menu",
            "bigFont.fnt"
        );

        title->setPosition(
            winSize.width / 2,
            winSize.height / 2 + 60
        );

        this->addChild(title);

        auto label = CCLabelBMFont::create(
            "Hello Geode!",
            "goldFont.fnt"
        );

        label->setPosition(
            winSize.width / 2,
            winSize.height / 2
        );

        this->addChild(label);

        return true;
    }
};

class $modify(MenuLayer) {
    bool init() {
        if (!MenuLayer::init())
            return false;

        auto winSize = CCDirector::sharedDirector()->getWinSize();

        auto sprite = CCSprite::create("nemo.png");

        if (!sprite) {
            sprite = CCSprite::createWithSpriteFrameName(
                "GJ_infoIcon_001.png"
            );
        }

        auto button = CCMenuItemSpriteExtra::create(
            sprite,
            this,
            menu_selector(MenuLayer::onNemoButton)
        );

        auto menu = this->getChildByID("bottom-menu");

        if (!menu) {
            menu = CCMenu::create();
            menu->setPosition({0, 0});
            this->addChild(menu);
        }

        button->setPosition({
            winSize.width - 40,
            40
        });

        static_cast<CCMenu*>(menu)->addChild(button);

        return true;
    }

    void onNemoButton(CCObject*) {
        auto scene = CCDirector::sharedDirector()->getRunningScene();

        auto existing = scene->getChildByTag(99999);

        if (existing) {
            existing->removeFromParent();
            return;
        }

        auto menu = NemoMenu::create();
        menu->setTag(99999);

        scene->addChild(menu, 999);
    }
};		/**
		 * We call the original init function so that the
		 * original class is properly initialized.
		 */
		if (!MenuLayer::init()) {
			return false;
		}

		/**
		 * You can use methods from the `geode::log` namespace to log messages to the console,
		 * being useful for debugging and such. See this page for more info about logging:
		 * https://docs.geode-sdk.org/tutorials/logging
		*/
		log::debug("Hello from my MenuLayer::init hook! This layer has {} children.", this->getChildrenCount());

		/**
		 * See this page for more info about buttons
		 * https://docs.geode-sdk.org/tutorials/buttons
		*/
		auto myButton = CCMenuItemSpriteExtra::create(
			CCSprite::createWithSpriteFrameName("GJ_likeBtn_001.png"),
			this,
			/**
			 * Here we use the name we set earlier for our modify class.
			*/
			menu_selector(MyMenuLayer::onMyButton)
		);

		/**
		 * Here we access the `bottom-menu` node by its ID, and add our button to it.
		 * Node IDs are a Geode feature, see this page for more info about it:
		 * https://docs.geode-sdk.org/tutorials/nodetree
		*/
		auto menu = this->getChildByID("bottom-menu");
		menu->addChild(myButton);

		/**
		 * The `_spr` string literal operator just prefixes the string with
		 * your mod id followed by a slash. This is good practice for setting your own node ids.
		*/
		myButton->setID("my-button"_spr);

		/**
		 * We update the layout of the menu to ensure that our button is properly placed.
		 * This is yet another Geode feature, see this page for more info about it:
		 * https://docs.geode-sdk.org/tutorials/layouts
		*/
		menu->updateLayout();

		/**
		 * We return `true` to indicate that the class was properly initialized.
		 */
		return true;
	}

	/**
	 * This is the callback function for the button we created earlier.
	 * The signature for button callbacks must always be the same,
	 * return type `void` and taking a `CCObject*`.
	*/
	void onMyButton(CCObject*) {
		FLAlertLayer::create("Geode", "Hello from my custom mod!", "OK")->show();
	}
};
