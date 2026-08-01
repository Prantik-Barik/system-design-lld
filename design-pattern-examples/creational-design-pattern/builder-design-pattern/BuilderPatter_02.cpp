#include <iostream>
#include <string>

using namespace std;

/*
Builder Pattern:
The Builder Pattern is a creational design pattern used when an object has
many configuration options. Instead of passing many values to a large
constructor, we set values step by step using a builder and finally call build().

Advantages:
1. Makes object creation readable.
2. Handles optional fields cleanly using default values.
3. Avoids constructor overloading with many parameter combinations.
4. Keeps object creation logic separate from the final object.
*/

class InstagramProfile {
private:
    string username;
    string displayName;
    string bio;
    string profilePicture;
    string website;
    bool privateAccount;
    bool verifiedBadge;
    string themeColor;

public:
    class Builder;

private:
    // Private constructor: InstagramProfile can only be created through Builder.
    InstagramProfile(const Builder& builder);

public:
    string getUsername() const {
        return username;
    }

    string getDisplayName() const {
        return displayName;
    }

    string getBio() const {
        return bio;
    }

    string getProfilePicture() const {
        return profilePicture;
    }

    string getWebsite() const {
        return website;
    }

    bool isPrivateAccount() const {
        return privateAccount;
    }

    bool hasVerifiedBadge() const {
        return verifiedBadge;
    }

    string getThemeColor() const {
        return themeColor;
    }

    void display() const {
        cout << "InstagramProfile [username=" << username
             << ", displayName=" << displayName
             << ", bio=" << bio
             << ", profilePicture=" << profilePicture
             << ", website=" << website
             << ", privateAccount=" << (privateAccount ? "true" : "false")
             << ", verifiedBadge=" << (verifiedBadge ? "true" : "false")
             << ", themeColor=" << themeColor
             << "]" << endl;
    }

    class Builder {
    private:
    // Assign default values to the InstagramProfile variables in the Builder class.
        string username;
        string displayName = "New User";
        string bio = "";
        string profilePicture = "default-profile.png";
        string website = "";
        bool privateAccount = false;
        bool verifiedBadge = false;
        string themeColor = "Default";

        friend class InstagramProfile;

    public:
    // re-assign  the values of whichever variables are passed to the Builder class.
        Builder(const string& username) {
            this->username = username;
        }

        Builder* setDisplayName(const string& displayName) {
            this->displayName = displayName;
            return this;
        }

        Builder* setBio(const string& bio) {
            this->bio = bio;
            return this;
        }

        Builder* setProfilePicture(const string& profilePicture) {
            this->profilePicture = profilePicture;
            return this;
        }

        Builder* setWebsite(const string& website) {
            this->website = website;
            return this;
        }

        Builder* setPrivate(bool privateAccount) {
            this->privateAccount = privateAccount;
            return this;
        }

        Builder* setVerified(bool verifiedBadge) {
            this->verifiedBadge = verifiedBadge;
            return this;
        }

        Builder* setThemeColor(const string& themeColor) {
            this->themeColor = themeColor;
            return this;
        }

        InstagramProfile build() const {
            return InstagramProfile(*this);
        }
    };
};

InstagramProfile::InstagramProfile(const Builder& builder) {
    username = builder.username;
    displayName = builder.displayName;
    bio = builder.bio;
    profilePicture = builder.profilePicture;
    website = builder.website;
    privateAccount = builder.privateAccount;
    verifiedBadge = builder.verifiedBadge;
    themeColor = builder.themeColor;
}

int main() {
    InstagramProfile::Builder builder("prantik_dev");
    builder.setDisplayName("Prantik")
        ->setBio("Software developer | C++ | System Design")
        ->setProfilePicture("prantik.jpg")
        ->setWebsite("https://example.com")
        ->setPrivate(false)
        ->setVerified(true)
        ->setThemeColor("Blue")
        ->build();

    InstagramProfile profile1 = builder.build();

    InstagramProfile::Builder builder2("travel_daily");
    builder2.setDisplayName("Travel Daily")
        ->setBio("Photos from around the world")
        ->setProfilePicture("travel.png")
        ->setPrivate(true);
    InstagramProfile profile2 = builder2.build();

    profile1.display();
    profile2.display();

    return 0;
}
